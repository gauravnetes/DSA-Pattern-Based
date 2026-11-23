# LC 347: Top K Frequent Elements

**Pattern Trigger:**

* The problem asks for the **"Top K"** or **"K most frequent"** elements in a dataset.
* The problem requires a time complexity strictly better than $\mathcal{O}(N \log N)$ (ruling out full sorting).

### Common Pitfall: `std::map` Does Not Sort by Frequency

A frequent mistake is counting frequencies in an ordered `std::map<int, int>` and iterating through the first $K$ entries.
* `std::map` sorts strictly by **key** (the element's value), **not** by its mapped value (the frequency).
* Always use `std::unordered_map<int, int>` for the initial frequency count to keep it at $\mathcal{O}(N)$ average time, then decouple the ranking step using either a **Min-Heap** or **Bucket Sort**.

---

### Approach 1: Hash Map + Min-Heap ($\mathcal{O}(N \log K)$)

Reuse the exact size-$K$ Min-Heap pattern from LC 215.
* Store pairs of `{frequency, number}` in the Min-Heap.
* In C++, `std::pair` comparison checks `.first` (frequency) before `.second` (number).
* Whenever the heap size exceeds $K$, `.pop()` evicts the element with the *smallest* frequency, trapping the $K$ most frequent elements inside.

#### Code Template (Min-Heap)

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        // Min-Heap storing {frequency, number}
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> minH;

        for (const auto& [num, count] : freq) {
            minH.push({count, num});
            if (minH.size() > k) {
                minH.pop(); // Evict the lowest frequency element
            }
        }

        vector<int> res;
        while (!minH.empty()) {
            res.push_back(minH.top().second);
            minH.pop();
        }

        return res;
    }
};
```

---

### Approach 2: Hash Map + Bucket Sort ($\mathcal{O}(N)$ Optimal)

**Key Insight:** No element can appear more than $N$ times (where $N$ is the size of `nums`). Because frequencies are strictly bounded by $[1, N]$, we can use array indices as the frequencies themselves to achieve linear time.

1. Count frequencies in an `unordered_map`.
2. Create a 2D vector `bucket` of size $N + 1$, where `bucket[i]` stores a list of all numbers that appear exactly `i` times.
3. Sweep backwards from `i = n` down to `1`, collecting numbers until `res.size() == k`.

#### Code Template (Bucket Sort)

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mp;

        for (int num : nums) {
            mp[num]++;
        }

        // Index represents frequency (1 to n); default constructor creates empty inner vectors
        vector<vector<int>> bucket(n + 1);
        for (const auto& [num, freq] : mp) {
            bucket[freq].push_back(num);
        }

        vector<int> res;
        // Sweep from highest possible frequency down to 1
        for (int i = n; i >= 1 && res.size() < k; i--) {
            // Read without mutating the bucket to avoid pop_back typos
            for (int num : bucket[i]) {
                res.push_back(num);
                if (res.size() == k) break;
            }
        }

        return res;
    }
};
```

---

### Complexity Comparison

| Approach | Time Complexity | Space Complexity | Best Use Case |
| :--- | :--- | :--- | :--- |
| **Min-Heap** | $\mathcal{O}(N \log K)$ | $\mathcal{O}(N + K)$ | Streaming data or when $K \ll N$. |
| **Bucket Sort** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Static arrays where strict linear time is required. |

### Critical C++ Traps to Memorize

1. **The Outer vs. Inner `.pop_back()` Trap:** When using a `while (!bucket[i].empty())` loop, accidentally writing `bucket.pop_back()` instead of `bucket[i].pop_back()` destroys the outer 2D vector and triggers a Heap-Buffer-Overflow / Segfault. **Fix:** Use a non-mutating range-based `for (int num : bucket[i])` loop instead.
2. **Clean 2D Vector Initialization:** `vector<vector<int>> bucket(n + 1);` automatically initializes `n + 1` empty inner vectors—no need for verbose `vector<int>({})` arguments.