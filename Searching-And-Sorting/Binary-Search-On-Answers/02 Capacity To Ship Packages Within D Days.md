# LC 1011: Capacity To Ship Packages Within D Days

**Pattern Trigger:**

* The problem asks to **"Minimize the Maximum"** (e.g., least weight capacity, minimize the largest sum).

* The answer lies on a monotonic boolean boundary (if a 15kg ship works, a 16kg ship works, but a 14kg ship fails).

* Validating a hypothetical answer takes a simple $\mathcal{O}(N)$ linear scan, whereas mathematically calculating the exact distribution is highly complex.

### The Search Space (Boundaries)

* **Minimum Possible Answer (`l`):** You cannot split a package. Therefore, the absolute smallest capacity the ship must have is the weight of the single heaviest package. (`*max_element`)

* **Maximum Possible Answer (`r`):** If you only have 1 day, the ship must be large enough to carry all packages at once. (`std::accumulate`)

### The State-First Framework for Validation

To avoid dropped variables and flipped inequalities, build your verification loop by answering three isolated questions:

1. **The Violation Trigger:** At what exact moment does the current state become illegal?
   * *Logic:* When adding the *current* package overflows the ship.
   * *Code:* `if (currWt + wt > cap)`

2. **The State Reset:** What variables die, and what survives?
   * *Logic:* A new day is required (`reqDays++`). The current package doesn't disappear; it gets loaded as the first item on the *new* ship.
   * *Code:* `currWt = wt;`

3. **The Happy Path:** What happens if there is no violation?
   * *Logic:* Just keep loading the current ship.
   * *Code:* `else { currWt += wt; }`

### Code Template

```cpp
class Solution {
public:
    // Helper to validate if a specific capacity works within 'days'
    bool shipAllPackages(const vector<int>& weights, int days, int cap) {
        int reqDays = 1; 
        int currWt = 0;
        
        for (const int& wt : weights) {
            // 1. Violation Trigger
            if(currWt + wt > cap) { 
                reqDays++;     // 2a. Reset State (increment days)
                currWt = wt;   // 2b. Survive (carry package to next day)
            } else {
                // 3. Happy Path
                currWt += wt; 
            }
        }
        return reqDays <= days; 
    }

    int shipWithinDays(vector<int>& weights, int days) {
        // l = max single package weight
        int l = *max_element(weights.begin(), weights.end()); 
        
        // r = sum of all packages. 
        // CRITICAL TRAP: Use 0LL (long long) to prevent integer overflow during sum!
        long long r = accumulate(weights.begin(), weights.end(), 0LL); 

        long long res = 0;
        
        while (l <= r) {
            long long mid = l + (r - l) / 2;
            
            if (shipAllPackages(weights, days, mid)) {
                res = mid;     // Lock in valid answer
                r = mid - 1;   // Try to find a smaller, tighter capacity
            } else {
                l = mid + 1;   // Capacity too small, must expand
            }
        }
        return res; 
    }
};
```

### Critical C++ Traps to Memorize:

1. **The `0LL` Accumulate Trap:** `accumulate(..., 0)` defaults to a 32-bit `int`. If the sum of the array exceeds $2.14 \times 10^9$, your code will throw a Runtime Error (Signed Integer Overflow). Always use `0LL` to force a 64-bit sum.
2. **Pass by Reference:** Always use `const vector<int>& weights` or `vector<int>& weights` in helper functions to prevent $\mathcal{O}(N)$ memory copies on every iteration.