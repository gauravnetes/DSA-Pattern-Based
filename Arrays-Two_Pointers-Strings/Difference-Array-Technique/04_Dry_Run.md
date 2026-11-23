# Maximize Frequency of an Element (Difference Array Pattern)

## 📌 Problem Context
- **Goal:** Maximize the frequency of any element in an array by incrementing or decrementing values by at most `k`.
- **Constraint:** You can perform at most `numOperations` total changes.
- **Key Realization:** Instead of checking every element against every other element $\mathcal{O}(N^2)$, we can use a **Difference Array (Line Sweep)** to check the coverage of all ranges in $\mathcal{O}(N + \text{maxVal})$ time.

---

## 🔍 Example Dry Run & Visualization

**Input:**
`nums = [1, 2, 4]`
`k = 1`
`numOperations = 1`

**Setup:**
`maxVal = 4 + 1 = 5` (Array bounds pad to `maxVal + 2` to prevent out-of-bounds on `r+1`)
`diff = [0, 0, 0, 0, 0, 0, 0]`

### Step 1: Building the Difference Array
For each number, calculate its reach `[l, r] = [num - k, num + k]` and mark the `diff` boundaries: `diff[l]++` and `diff[r+1]--`.

| Index | Element | Reach `[l, r]` | `diff` Updates | Current `diff` Array State |
| :--- | :--- | :--- | :--- | :--- |
| `i=0` | `1` | `[0, 2]` | `diff[0]+1`, `diff[3]-1` | `[1, 0, 0, -1, 0, 0, 0]` |
| `i=1` | `2` | `[1, 3]` | `diff[1]+1`, `diff[4]-1` | `[1, 1, 0, -1, -1, 0, 0]` |
| `i=2` | `4` | `[3, 5]` | `diff[3]+1`, `diff[6]-1` | `[1, 1, 0, 0, -1, 0, -1]` |

---

### Step 2: Prefix Sum & Evaluation
We sweep through all possible targets from `0` to `maxVal`. The prefix sum of `diff` tells us exactly how many numbers are within `k` distance of the current target. 

* **`totalInRange`:** Total numbers close enough to become `target`.
* **`targetFreq`:** Numbers already equal to `target` (cost 0 operations).
* **`needConversion`:** `totalInRange - targetFreq`.
* **`usedOps`:** `min(needConversion, numOperations)`.

| Target | `diff[t]` | Prefix Sum (`totalInRange`) | `targetFreq` | `needConversion` | `usedOps` (Max 1) | Final Frequency |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **0** | `1` | `1` | `0` | `1 - 0 = 1` | `1` | `0 + 1 = 1` |
| **1** | `1` | `2` | `1` | `2 - 1 = 1` | `1` | `1 + 1 = 2` |
| **2** | `0` | `2` | `1` | `2 - 1 = 1` | `1` | `1 + 1 = 2` |
| **3** | `0` | `2` | `0` | `2 - 0 = 2` | `1` | `0 + 1 = 1` |
| **4** | `-1` | `1` | `1` | `1 - 1 = 0` | `0` | `1 + 0 = 1` |
| **5** | `0` | `1` | `0` | `1 - 0 = 1` | `1` | `0 + 1 = 1` |

**Result:** The maximum frequency we can achieve is **2** (by targeting either `1` or `2`).

---

## 💻 C++ Implementation

```cpp
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int maxVal = *max_element(nums.begin(), nums.end()) + k; 

        // Size maxVal + 2 prevents Out-of-Bounds on diff[r+1]
        vector<int> diff(maxVal + 2, 0); 
        unordered_map<int, int> freq; 

        // 1. Build the Line Sweep boundaries
        for(int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++; // Track exact matches
            
            int l = max(nums[i]-k, 0); 
            int r = min(nums[i]+k, maxVal); 

            diff[l]++; 
            diff[r+1]--; 
        }

        int res = 1; 
        
        // 2. Prefix sum evaluation
        for(int target = 0; target <= maxVal; target++) {
            // diff[target] becomes the rolling prefix sum
            diff[target] += (target > 0 ? diff[target-1] : 0); 
            
            // C++ Map Quirk: If 'target' isn't in nums, it creates the key and defaults to 0
            int targetFreq = freq[target]; 
            
            // Exclude elements that are ALREADY at the target (they don't cost operations)
            int needConversion = diff[target] - targetFreq; 
            
            // We can only convert as many as our numOperations budget allows
            int maxPossibleFreq = min(needConversion, numOperations); 
            
            res = max(res, maxPossibleFreq + targetFreq); 
        }

        return res; 
    }
};