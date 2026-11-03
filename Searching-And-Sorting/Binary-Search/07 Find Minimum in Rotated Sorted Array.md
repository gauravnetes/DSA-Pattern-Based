# LC 153 & 154: Find Minimum in Rotated Sorted Array (with Duplicates)

**Pattern Trigger:**
* Array is sorted, rotated, and may contain duplicate values.
* Asked to find the minimum element.

### The "Running Minimum" Approach
Instead of strictly relying on pointer convergence (where `l` and `r` trap the minimum), this method maintains a global tracker (`resIdx`) and aggressively shrinks the search space.

**Key Mechanics:**
1. **Track Minimum:** On every iteration, compare `nums[mid]` against your current best answer (`nums[resIdx]`). If it's smaller, update it.
2. **Duplicate Skipping:** The inner `while` loops eagerly skip identical adjacent elements at the edges. This prevents the binary search from getting confused when `nums[l] == nums[mid] == nums[r]`.
3. **Binary Search the Drop:** 
   * If `nums[mid] > nums[r]`, the array "drops" to the right. The minimum must be right: `l = mid + 1`.
   * Else, the drop is to the left (or we are on it). Because we already saved `mid` in `resIdx`, we can safely aggressively shrink left: `r = mid - 1`.

### Code Template

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size(); 
        int l = 0, r = n - 1; 
        int resIdx = 0; // Tracks the index of the minimum element

        while(l <= r) {
            // Eagerly skip duplicates at the boundaries
            while(l < r && nums[l] == nums[l+1]) l++; 
            while(l < r && nums[r] == nums[r-1]) r--; 
            
            int mid = l + (r - l) / 2; 
            
            // Record the minimum seen so far
            if(nums[mid] < nums[resIdx]) {
                resIdx = mid; 
            }
            
            // Standard rotated array binary search logic
            if(nums[mid] > nums[r]) {
                l = mid + 1; 
            } else {
                r = mid - 1; // Safe because of resIdx tracking
            }
        }

        return nums[resIdx]; 
    }
};
```

**Complexity Analysis:**
* **Time Complexity:** $\mathcal{O}(\log N)$ on average. However, in the worst-case scenario where all elements are identical (e.g., `[2, 2, 2, 2, 2]`), the inner `while` loops will scan every element, degrading the time to $\mathcal{O}(N)$. 
* **Space Complexity:** $\mathcal{O}(1)$.