# LC 215: Kth Largest Element (Quickselect)

**Pattern Trigger:**

* The problem asks for the "Kth largest" or "Kth smallest" element.
* The interviewer explicitly asks for an $\mathcal{O}(N)$ average time complexity solution, or prohibits the use of Heaps/Sorting.

### The Core Concept: Quickselect

Quickselect is a partial QuickSort. Instead of sorting both halves of the array after partitioning, you only recursively search the half where the $K$th element must logically exist.

1. **Partitioning:** Pick a pivot. Move all elements greater than the pivot to the left, and smaller elements to the right (for descending order).
2. **Targeting:** The pivot is now in its absolute final sorted position. 
   * If its index `== k - 1`, you found the answer.
   * If its index `> k - 1`, the answer is in the left half.
   * If its index `< k - 1`, the answer is in the right half.

### The Lomuto Partition vs. Hoare Partition

* **Hoare Partition (Two Pointers moving inward):** Faster in theory but extremely prone to index out-of-bounds (Segfaults) and infinite loops if `if/else` logic is slightly misaligned.
* **Lomuto Partition (One Pointer chasing another):** Uses a simple `for` loop. It is mathematically impossible to go out-of-bounds. **Always use Lomuto for Quickselect in interviews.**

### The "Time Limit Exceeded" (TLE) Trap

If you pick the first or last element as the pivot, and the array is already sorted (or filled with duplicates like `[2, 2, 2, 2]`), the pivot does nothing. It shrinks the search space by only 1 element per pass, causing the $\mathcal{O}(N)$ algorithm to aggressively degrade into $\mathcal{O}(N^2)$. 

* **The Fix:** Always pick a **random** pivot index and swap it with the last element before starting the Lomuto partition.

### Code Template (Randomized Lomuto)

```cpp
class Solution {
public:
    int partition(vector<int> &nums, int L, int R) {
        // 1. Defeat the O(N^2) TLE Trap: Randomize Pivot
        int randIdx = L + rand() % (R - L + 1);
        swap(nums[randIdx], nums[R]); // Hide pivot at the very end
        
        int p = nums[R]; 
        int i = L; // 'i' acts as the boundary wall for elements >= pivot
        
        // 2. Lomuto Partition (Descending Order)
        for(int j = L; j < R; j++) {
            if(nums[j] >= p) {
                // Throw larger elements over the wall to the left
                swap(nums[i], nums[j]); 
                i++; // Move the wall up
            }
        }
        
        // 3. Put the pivot in its final, correct spot
        swap(nums[i], nums[R]); 
        return i; 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int L = 0, R = nums.size() - 1; 

        // Binary Search style boundary reduction
        while(L <= R) {
            int pivotIdx = partition(nums, L, R); 
            
            // Note: k-1 because we are looking for the Kth element (0-indexed)
            if(pivotIdx == k - 1) {
                return nums[pivotIdx]; 
            } else if(pivotIdx > k - 1) {
                R = pivotIdx - 1; 
            } else {
                L = pivotIdx + 1; 
            }
        } 

        return -1; 
    }
};
```

### Complexity

* **Time:** $\mathcal{O}(N)$ average time. $\mathcal{O}(N^2)$ worst-case (virtually impossible with a randomized pivot).
* **Space:** $\mathcal{O}(1)$ auxiliary space (iterative version).