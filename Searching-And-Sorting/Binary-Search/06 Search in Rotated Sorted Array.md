# LC 33: Search in Rotated Sorted Array (Two-Pass Method)

**Pattern Trigger:**
* Array is sorted but shifted/rotated.
* Strict $\mathcal{O}(\log N)$ time constraint.

**The Strategy:**
Instead of a complex one-pass algorithm, we break the problem into two simpler $\mathcal{O}(\log N)$ binary searches:
1. Find the `pivotIdx` (the index of the minimum element).
2. Perform a standard Binary Search on the appropriate sorted half (either left of the pivot or right of the pivot).

---

### Step 1: Finding the Pivot Index (The Core Logic)
As derived from the handwritten notes, finding the minimum index in $\mathcal{O}(\log N)$ relies on comparing `nums[mid]` with the rightmost boundary `nums[r]`.

* **The Loop:** `while (l < r)` ensures the loop breaks exactly when `l` and `r` collide on the minimum element.
* **Condition 1 (The Break):** `if (nums[mid] > nums[r])`
  * Example: `[3, 4, 5, 1, 2]` where `mid` points to `5` and `r` points to `2`. 
  * *Note Insight:* This is an invalid state for a strictly sorted array (`nums[r]` should be $>$ `nums[mid]`). It means the "drop" (pivot) is definitely sitting somewhere in the right-half.
  * **Action:** `l = mid + 1;`
* **Condition 2 (The Sorted Half):** `else // nums[mid] <= nums[r]`
  * Example: `mid` points to `1` and `r` points to `2`.
  * *Note Insight:* This is a valid sorted state. Where `mid` is standing, everything to the right is greater. The pivot could be `mid` itself, but it cannot be to the right.
  * **Action:** `r = mid;` (We don't do `mid - 1` because `mid` might be our answer!).
* **Return:** You can return `l` or `r` interchangeably because the `while(l < r)` condition guarantees they are pointing at the same index when the loop ends.

### Step 2: The Two-Pass Code Template

```cpp
class Solution {
public:
    // Helper 1: Standard Binary Search
    int bS(vector<int> &nums, int l, int r, int target) {
        while(l <= r) {
            int mid = l + (r - l) / 2; 
            if(nums[mid] == target) 
                return mid; 
            else if(nums[mid] < target) 
                l = mid + 1; 
            else 
                r = mid - 1; 
        }
        return -1; 
    }

    // Helper 2: Find Pivot / Minimum Index
    // CRITICAL: Always pass vector by reference (&) to avoid O(N) copy overhead!
    int findPivot(vector<int>& nums, int n) {
        int l = 0, r = n - 1; 
        while(l < r) {
            int mid = l + (r - l) / 2; 
            if(nums[mid] > nums[r]) 
                l = mid + 1; 
            else 
                r = mid; 
        }
        return r; // l and r have collided here
    }

    int search(vector<int>& nums, int target) {
        int n = nums.size(); 
        if (n == 0) return -1;

        int pivotIdx = findPivot(nums, n); 

        // Search the left half (from index 0 up to pivot - 1)
        int targetIdx = bS(nums, 0, pivotIdx - 1, target); 
        if(targetIdx != -1) 
            return targetIdx; 
        
        // If not found, search the right half (from pivot to the end)
        return bS(nums, pivotIdx, n - 1, target); 
    }
};
```

**Complexity:**
* **Time:** $\mathcal{O}(\log N)$ (Two non-nested binary searches: $\log N + \log N \approx \log N$).
* **Space:** $\mathcal{O}(1)$ (No extra memory used).