# LC 1552: Magnetic Force Between Two Balls / Aggressive Cows

**Pattern Trigger:**

* The problem explicitly asks to **"Maximize the Minimum"** (e.g., maximize the minimum distance between two balls, maximize the minimum payout).

* You are dealing with physical coordinates or positions that can be sorted.

* The search space is a range of possible distances (a monotonic boolean boundary: if a distance of 10 works, 9 definitely works. If 11 fails, 12 definitely fails).

### The "Maximize the Minimum" Inversion

This problem is the exact mathematical inverse of Book Allocation or Package Shipping. 
* In "Minimize the Max" (Shipping), when you find a valid answer, you move **left** (`r = mid - 1`) to find a smaller capacity.
* In "Maximize the Min" (Balls/Cows), when you find a valid answer, you move **right** (`l = mid + 1`) to greedily hunt for a larger, better distance.

### The Search Space (Boundaries)

* **Pre-requisite:** You **MUST** sort the array first. Binary search on positions only works if the coordinates are strictly increasing.

* **Minimum Possible Answer (`l`):** The smallest possible distance between any two items is `1` (assuming distinct positions).

* **Maximum Possible Answer (`r`):** The absolute maximum possible distance is placing one ball at the very first position and one at the very last position: `pos[n-1] - pos[0]`.

### The Validation Logic (Greedy Placement)

Unlike contiguous subarray sums, distance placement is purely greedy. You always place the first ball at the first available spot (`pos[0]`), and then scan forward for the very next spot that satisfies the minimum distance `mid`.

1. **The Condition:** Does the current position minus the last placed position meet or exceed the target distance? `if(pos[i] - prev >= force)`
2. **The Action:** Place a ball (`cntBalls++`), and update your anchor point (`prev = pos[i]`).

### Code Template

```
class Solution {
public:
    // Helper to validate if we can place 'm' balls with at least 'force' distance
    bool canPlaceAllBalls(const vector<int> &pos, int force, int m) {
        int prev = pos[0];   // Always place the first ball at the first position
        int cntBalls = 1; 

        for(int i = 1; i < pos.size(); i++) {
            // If the gap is large enough, place the next ball here
            if(pos[i] - prev >= force) {
                cntBalls++; 
                prev = pos[i]; // Update the anchor point
            }
            
            // Early exit optimization: we placed all required balls
            if(cntBalls == m) 
                break; 
        }

        // Defensive practice: always use >= instead of == just in case 
        // the early exit is modified or removed in the future.
        return cntBalls >= m; 
    }

    int maxDistance(vector<int>& pos, int m) {
        int n = pos.size(); 
        
        // CRITICAL: Must sort the physical coordinates first!
        sort(pos.begin(), pos.end()); 

        int l = 1; 
        int r = pos[n-1] - pos[0]; 
        int maxMinDist = 1; 

        // Binary Search on Answer Range
        while(l <= r) {
            int mid = l + (r - l) / 2; 
            
            if(canPlaceAllBalls(pos, mid, m)) {
                maxMinDist = mid; // Lock in the valid distance
                l = mid + 1;      // INVERSION: Try to find a LARGER valid distance
            } else {
                r = mid - 1;      // Target distance is too large, must shrink it
            }
        }

        return maxMinDist; 
    }
};
```

### Key Differences from "Minimize the Max" Traps

1. **No Accumulation:** Because you are checking the *difference* between coordinates (`pos[i] - prev`), and standard constraints keep coordinates around $10^9$, differences will never exceed the 32-bit `int` limit. You do not need `long long` here.
2. **Sorting is Mandatory:** If you forget `sort(pos.begin(), pos.end())`, the greedy placement logic instantly breaks because jumping from `pos[i]` to `pos[i-1]` could result in negative distances.