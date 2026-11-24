# LC 451: Sort Characters By Frequency

**Pattern Trigger:**

* The problem asks to reorder or group characters strictly by their frequency in descending order.
* Unlike integer-based frequency problems (like LC 347), the alphabet size $K$ is bounded by a small constant (ASCII: $K \le 128$, alphanumeric: $K \le 62$).

### Critical Trap: The `ch - 'a'` Offset Hazard

LC 451 contains **uppercase letters, lowercase letters, and digits** (`'A'-'Z'`, `'a'-'z'`, `'0'-'9'`).

* Computing `ch - 'a'` on `'A'` (ASCII $65$) produces $-32$.
* Using an `unordered_map<int, int>` hides this bug because hash maps accept negative keys, but switching to a `vector<int>(26)` will immediately cause an out-of-bounds Segmentation Fault.
* **Fix:** Never subtract `'a'` when uppercase letters or digits are allowed. Use a stack-allocated ASCII table `int freq[128] = {0};` to index characters directly with zero hashing overhead.

---

### Approach 1: ASCII Array + Max-Heap (Best for ASCII)

Because there are at most $K \le 128$ unique characters, pushing them into a Max-Heap takes $\mathcal{O}(K \log K) = \mathcal{O}(1)$ time and $\mathcal{O}(1)$ auxiliary space.

```cpp
class Solution {
public:
    string frequencySort(string s) {
        // Stack-allocated frequency table handles all ASCII chars natively
        int freq[128] = {0};
        for (char ch : s) {
            freq[ch]++;
        }

        // Max-Heap storing {frequency, character}
        priority_queue<pair<int, char>> maxH;
        for (int c = 0; c < 128; c++) {
            if (freq[c] > 0) {
                maxH.push({freq[c], static_cast<char>(c)});
            }
        }

        string res;
        res.reserve(s.length()); // Pre-allocate memory to avoid reallocations

        while (!maxH.empty()) {
            auto [count, ch] = maxH.top();
            maxH.pop();
            res.append(count, ch); // Bulk append instead of a while(count--) loop
        }

        return res;
    }
};
```

---

### Approach 2: ASCII Array + Bucket Sort (Best for Unbounded Alphabets)

Since no character can appear more than `maxFreq` times (at most $N$), we can map frequencies directly to array indices and sweep backward from `maxFreq` down to `1`.

```cpp
class Solution {
public:
    string frequencySort(string s) {
        int freq[128] = {0};
        int maxFreq = 0;

        for (char ch : s) {
            maxFreq = max(maxFreq, ++freq[ch]);
        }

        // Sizing to maxFreq + 1 avoids allocating unused buckets up to N
        // vector<string> is cleaner and more compact than vector<vector<char>>
        vector<string> buckets(maxFreq + 1);
        for (int c = 0; c < 128; c++) {
            if (freq[c] > 0) {
                buckets[freq[c]].push_back(static_cast<char>(c));
            }
        }

        string res;
        res.reserve(s.length());

        for (int f = maxFreq; f >= 1; f--) {
            for (char ch : buckets[f]) {
                res.append(f, ch);
            }
        }

        return res;
    }
};
```

---

### Complexity & Trade-Off Comparison

| Approach | Time Complexity | Auxiliary Space | Best Use Case |
| :--- | :--- | :--- | :--- |
| **Max-Heap** | $\mathcal{O}(N + K \log K) \rightarrow \mathcal{O}(N)$ | $\mathcal{O}(K) \rightarrow \mathcal{O}(1)$ | Fixed ASCII alphabet ($K \le 128$). Avoids allocating up to $N$ empty buckets. |
| **Bucket Sort** | $\mathcal{O}(N + \text{maxFreq}) \rightarrow \mathcal{O}(N)$ | $\mathcal{O}(\text{maxFreq}) \rightarrow \mathcal{O}(N)$ | Unbounded alphabets (e.g., Unicode where $K \approx N$) where $K \log K$ is no longer constant. |

### Industry-Standard C++ Habits

1. **Pre-allocate Output Strings (`res.reserve(s.length())`):** Prevents repeated heap reallocations and memory copies as the string grows to size $N$.
2. **Bulk Character Insertion (`res.append(count, ch)`):** Cleaner and faster than a manual `while (count--) res += ch;` loop.
3. **Skip `unordered_map` for ASCII:** `int freq[128] = {0};` lives on the stack, is L1-cache friendly, and avoids hash collisions entirely.