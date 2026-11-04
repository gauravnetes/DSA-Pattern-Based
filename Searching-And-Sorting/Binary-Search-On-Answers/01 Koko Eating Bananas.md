# LC 875: Koko Eating Bananas

**Pattern Trigger:**

* You are asked to find the **minimum** or **maximum** rate, speed, or capacity to complete a task.
* There is a strict constraint (e.g., must finish within `h` hours).
* The answer has a defined range (e.g., $1$ to maximum pile size).

### First Principles: Binary Search on Answers

Why does Binary Search work here when there is no physical array to search? 

It works because the *answer space* is **monotonic**.
1. **The Range:** Koko's minimum possible eating speed is $1$ banana/hour. Her maximum useful speed is the size of the largest pile (because she can only eat from one pile per hour, eating faster than the largest pile doesn't save any more time).
2. **The Monotonicity:** If Koko can finish all bananas at a speed of $K$, she can *guarantee* finishing them at $K + 1, K + 2, \dots$ etc. If she *cannot* finish at speed $K$, she definitely cannot finish at $K - 1$.
3. **The Mapping:** This creates a boolean array that looks exactly like `[False, False, False, True, True, True]`. Finding the minimum eating speed is mathematically identical to finding the **Lower Bound** of `True`.

### Code Template

```cpp
class Solution {
public:
    // Helper function to validate if a speed (mid) works
    bool canEatAllBananas(vector<int> &piles, int mid, int h) {
        long long actualHrs = 0; // CRITICAL: long long to prevent integer overflow
        
        for(int &x : piles) {
            actualHrs += (x / mid); 
            if(x % mid != 0) 
                actualHrs++; 
        }
        return actualHrs <= h; 
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1; 
        int r = *max_element(piles.begin(), piles.end()); 
        int res = 0; 

        // Binary Search on the Answer Range [1, max_element]
        while(l <= r) {
            int mid = l + (r - l) / 2; 
            
            if(canEatAllBananas(piles, mid, h)) {
                res = mid;     // Record the valid speed
                r = mid - 1;   // Try to find a slower (better) speed to the left
            } else {
                l = mid + 1;   // Speed too slow, must search to the right
            }
        }

        return res; 
    }
};
```

### Guardrails & Edge Cases

* **The Accumulator Overflow Trap:** If `h` is very large (e.g., $10^9$) and the piles are massive, testing a slow speed like $1$ will cause the total hours to exceed the 32-bit integer limit ($2.14 \times 10^9$). The accumulator variable (`actualHrs`) **must** be a `long long`.
* **Zero Speed:** `l` must start at $1$, not $0$. You cannot divide by $0$ in your helper function.

### Complexity Analysis

* **Time:** $\mathcal{O}(N \log M)$ 
  * Finding the max element takes $\mathcal{O}(N)$.
  * The binary search space is $M$ (where $M$ is the max element), taking $\mathcal{O}(\log M)$ steps.
  * For each step, we iterate through all $N$ piles, costing $\mathcal{O}(N)$.
  * Total: $\mathcal{O}(N) + \mathcal{O}(N \log M) = \mathcal{O}(N \log M)$.
* **Space:** $\mathcal{O}(1)$ (No auxiliary data structures used).