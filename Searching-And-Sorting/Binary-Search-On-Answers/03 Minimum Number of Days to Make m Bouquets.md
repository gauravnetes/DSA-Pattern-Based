# LC 1482: Minimum Number of Days to Make m Bouquets

**Pattern Trigger:**

* Asking for the **minimum** days to achieve a target.

* Monotonic boolean boundary: If you can make the bouquets on day 10, you can definitely make them on day 11. If day 9 fails, day 8 definitely fails.

* Subarray constraint: The flowers for a single bouquet must be *adjacent* (continuous sequence).

### The State-First Framework (Continuous Segments)

When dealing with continuous segments (like adjacent flowers), the order in which you update your counters is critical. If you check your condition *before* updating the state, you risk the "Delayed Bouquet" bug, where a valid sequence at the very end of the array is ignored.

1. **The Violation Trigger:** What breaks the sequence?
   * *Logic:* If the flower hasn't bloomed yet (`b > days`), the continuous streak is dead.
   * *Code:* `count = 0;`
2. **The Happy Path:** What continues the sequence?
   * *Logic:* The flower has bloomed (`b <= days`), so we add it to our current streak.
   * *Code:* `count++;`
3. **The State Reset:** When is the goal met?
   * *Logic:* *After* adding the flower, did we hit exactly `k`? If so, lock in the bouquet and reset the streak.
   * *Code:* `if (count == k) { bouquetCnt++; count = 0; }`

### Code Template

```cpp
class Solution {
public: 
    bool canMakeAllBouquets(const vector<int>& bloomDay, int m, int k, int days) {
        int count = 0; 
        int bouquetCnt = 0; 

        for(const int &b : bloomDay) {
            // 1. Violation: The streak is broken
            if(b > days) {
                count = 0; 
            } 
            // 2. Happy Path: The streak continues
            else {
                count++; 
                // 3. State Reset: We finished exactly one bouquet!
                if(count == k) {
                    bouquetCnt++; 
                    count = 0; // Reset streak for the next bouquet
                }
            }
        }

        return bouquetCnt >= m; 
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size(); 

        // CRITICAL TRAP: m and k can be 10^9. m * k will overflow 32-bit int!
        // Multiply by 1LL to force 64-bit calculation.
        if(n < 1LL * m * k)
            return -1; 

        int l = *min_element(bloomDay.begin(), bloomDay.end()); 
        int r = *max_element(bloomDay.begin(), bloomDay.end()); 
        int res = 0; 
        
        while(l <= r) {
            int mid = l + (r - l) / 2; 

            if(canMakeAllBouquets(bloomDay, m, k, mid)) {
                res = mid;     // Lock in valid answer
                r = mid - 1;   // Try to find an earlier day
            } else {
                l = mid + 1;   // Day is too early, need more time
            }
        }
        return res; 
    }
};
```

### Edge Cases & C++ Execution Traps

* **The `1LL` Multiplication Cast:** If $m = 10^9$ and $k = 10^9$, $m \times k = 10^{18}$. A 32-bit `int` caps at $2 \times 10^9$. Writing `if (n < m * k)` causes an immediate integer overflow, wrapping around to a negative number, bypassing your base case and causing unexpected behavior. Always inject `1LL *` before multiplying two variables that could breach the $2 \times 10^9$ limit.
* **Pass by Reference:** Use `const vector<int>&` in the helper function to avoid an $\mathcal{O}(N)$ copy penalty on every binary search iteration.

**Complexity:**
* **Time:** $\mathcal{O}(N \log(\text{max} - \text{min}))$. Finding min/max is $\mathcal{O}(N)$. The binary search runs $\mathcal{O}(\log(\text{max} - \text{min}))$ times, and each check takes $\mathcal{O}(N)$. 
* **Space:** $\mathcal{O}(1)$.