# Maximize Frequency of an Element After Operations

**Pattern Trigger:**

* The problem asks you to maximize the frequency or count of identical elements.
* You are allowed to adjust elements within a specific range (e.g., $+/- k$).
* You have a limited budget or cap on how many total changes you can make (`numOperations`).
* **Key Indicator for this specific approach:** The constraints allow for a bounded maximum value, making it efficient to sweep across all possible targets rather than just the elements in the array.

### Core Technique: Difference Array (Line Sweep)

When you need to add $+1$ to a continuous range of indices `[L, R]` repeatedly, doing it with a standard loop takes $\mathcal{O}(N \times \text{Range})$, which causes TLE. 

Instead, use a **Difference Array**:
1. Add `1` to the start of the range: `diff[L]++`
2. Subtract `1` just after the end of the range: `diff[R+1]--`
3. After processing all elements, run a prefix sum `diff[i] += diff[i-1]`. `diff[i]` will now contain the exact number of overlapping intervals at that specific target.

### The Overlap Math & "Free" Matches

A major conceptual trap in this problem is understanding what the Difference Array actually counts. 

If an element `5` can reach anywhere in `[3, 7]`, we add `+1` to that entire range. This means the target `5` itself receives a `+1` from its own interval. 
* **`diff[target]`**: Total number of elements that *can* become `target` (distance $\le k$). This includes elements that are *already* `target`.
* **`targetFreq`**: Total number of elements that are already exactly `target`. Cost to convert = $0$ operations.
* **`needConversion`**: `diff[target] - targetFreq`. These are the elements that are close enough, but *require* spending an operation to pull them to the target.

You only spend your limited `numOperations` budget on the `needConversion` pool.

### The C++ Map Default Trap/Feature

When iterating through all possible targets, you will query `freq[target]` for numbers that never existed in the original array. 
* In C++, `unordered_map<int, int>` automatically creates a missing key and initializes its value to `0`. 
* This safely and effortlessly returns `0` for missing elements without needing an explicit `if (freq.count(target))` check. 

### Code Template

```cpp
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        // Find the absolute highest value we could possibly reach
        int maxVal = *max_element(nums.begin(), nums.end()) + k; 

        // diff array needs +2 to safely handle diff[r+1] for the max possible element
        vector<int> diff(maxVal + 2, 0); 
        unordered_map<int, int> freq; 

        for(int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++; // Track exactly how many 'free' matches exist

            // Calculate the valid reach of the current element
            int l = max(nums[i] - k, 0); 
            int r = min(nums[i] + k, maxVal); 

            // Apply Difference Array technique for O(1) range update
            diff[l]++; 
            // Decrease at r+1 so the +1 effect stops after 'r'
            diff[r+1]--; 
        }

        int res = 1; 
        
        // Line Sweep: evaluate every possible target
        for(int target = 0; target <= maxVal; target++) {
            // Resolve the difference array into a prefix sum (total overlaps)
            diff[target] += (target > 0 ? diff[target-1] : 0); 
            
            // 1. Free matches (already at target)
            int targetFreq = freq[target]; // Auto-returns 0 if not in map
            
            // 2. Elements that CAN reach target, but COST an operation
            int needConversion = diff[target] - targetFreq; 
            
            // 3. Cap the conversions by our operations budget
            int maxPossibleFreq = min(needConversion, numOperations); 
            
            // 4. Total = Converted Elements + Free Elements
            res = max(res, maxPossibleFreq + targetFreq); 
        }

        return res; 
    }
};
```