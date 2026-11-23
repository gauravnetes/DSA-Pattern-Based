# LC 3347: Maximum Frequency of an Element After Performing Operations II

**Pattern Trigger:**

* The problem is identical to standard frequency maximization, but the constraints (e.g., $k$ and $nums[i]$ up to $10^9$) make a standard contiguous Difference Array impossible due to Memory Limit Exceeded (MLE).
* You must transition to a **Sparse Line Sweep** using a `std::map` or a sorted array of events.

### The Sparse Line Sweep Upgrades

When moving from a flat `vector` to a `std::map` for your difference array, three fundamental shifts happen:

1. **No Out-of-Bounds:** You no longer need to calculate a `maxVal` or clamp your boundaries with `max(..., 0)`. A map easily stores negative coordinates and numbers far beyond the array elements. `l = nums[i] - k` and `r = nums[i] + k` are perfectly safe.

2. **The "Ghost Point" Trap:** A map iterator only stops at the exact events you insert. If you only insert `l` and `r + 1`, the sweep will skip over the actual elements of the array. You must force the map to pause at the array elements to evaluate the "free matches" by inserting a ghost point: `diff[nums[i]] += 0`.

3. **Hash Map Pollution:** If you use `int targetFreq = freq[target];` during the sweep, the `unordered_map` will automatically create a new key with a value of `0` for every single boundary point `l` and `r+1`. This causes massive memory reallocation and slows down the code. Always check existence first: `freq.count(target) ? freq[target] : 0`.

### Code Template (std::map Implementation)

```cpp
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        map<int, int> diff;            // Ordered map for the sweep
        unordered_map<int, int> freq;  // Tracks exact matches (cost = 0)

        // 1. Build the Sparse Difference Array (O(N log N))
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++;

            int l = nums[i] - k;
            int r = nums[i] + k;

            diff[l]++;
            diff[r + 1]--;

            // CRITICAL: Force the sweep to evaluate the actual element 
            // so we don't miss out on the 'free' matches.
            diff[nums[i]] += 0; 
        }

        int res = 1;
        int cumSum = 0;

        // 2. Line Sweep (O(N))
        for (auto it = diff.begin(); it != diff.end(); it++) {
            int target = it->first;
            
            // Resolve the prefix sum
            cumSum += it->second; 
            it->second = cumSum;  // Overwrite with total overlapping intervals

            // Use .count() to prevent polluting the hash map with '0' values
            int targetFreq = freq.count(target) ? freq[target] : 0;
            
            int needConversion = it->second - targetFreq;
            int maxPossibleFreq = min(needConversion, numOperations);
            
            res = max(res, maxPossibleFreq + targetFreq);
        }

        return res;
    }
};
```

### Pro-Tip: The $\mathcal{O}(N \log N)$ Speed Demon Optimization

While `std::map` works, it scatters data across the heap (cache misses). For maximum execution speed in competitive programming, you can flatten the map into a sorted `vector<pair<int, int>>` of events:

```cpp
vector<pair<int, int>> events;
for (int num : nums) {
    freq[num]++;
    events.push_back({num - k, 1});      // Start of range
    events.push_back({num + k + 1, -1}); // End of range
    events.push_back({num, 0});          // Ghost point for evaluation
}
sort(events.begin(), events.end());
```
You then iterate through the vector, accumulating the `second` values and evaluating the frequency exactly as you did with the map iterator.