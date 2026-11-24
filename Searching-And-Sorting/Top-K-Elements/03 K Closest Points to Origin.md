# LC 973: K Closest Points to Origin

**Pattern Trigger:**

* The problem asks for the **"K smallest"** or **"K closest"** elements based on a calculated metric (distance, score, difference).

* You do not need the final $K$ elements in strictly sorted order, and you want $\mathcal{O}(N \log K)$ time instead of sorting the entire dataset in $\mathcal{O}(N \log N)$.

### Core Concept 1: The Heap Inversion Rule

Always ask: **"What does `.pop()` evict when the heap size exceeds $K$?"**

* **To find the $K$ Largest (LC 215):** Use a **Min-Heap** of size $K$. `.pop()` evicts the *smallest* elements, trapping the $K$ largest inside.

* **To find the $K$ Closest / Smallest (LC 973):** Use a **Max-Heap** of size $K$. `.pop()` evicts the *farthest* (largest distance) points, trapping the $K$ closest inside.

### Core Concept 2: Avoid `sqrt()` and `pow()`

The Euclidean distance from the origin $(0, 0)$ is $\sqrt{x^2 + y^2}$.

* **The Integer Truncation Trap:** Storing `sqrt(...)` in an `int` truncates decimals (e.g., $\sqrt{1} = 1$ and $\sqrt{2} \approx 1.414$ both become `1`), breaking comparisons.

* **The Math Trick:** Because the square root function is strictly increasing for non-negative numbers:
  $$a < b \iff \sqrt{a} < \sqrt{b}$$
  Comparing the **squared distance** $x^2 + y^2$ yields the exact same ordering with zero floating-point precision loss and no `sqrt()`/`pow()` overhead.

### Code Template (Max-Heap with Coordinates)

```cpp
class Solution {
public:
    using P = pair<int, pair<int, int>>; // {squared_dist, {x, y}}

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Max-Heap: evicts the point with the largest distance when size > k
        priority_queue<P> maxH;

        for (const auto& point : points) {
            int x = point[0];
            int y = point[1];

            int distSq = x * x + y * y;
            maxH.push({distSq, {x, y}});

            if (maxH.size() > k) {
                maxH.pop(); // Throw away the farthest point
            }
        }

        vector<vector<int>> res;
        res.reserve(k); // Pre-allocate capacity to avoid reallocations

        while (!maxH.empty()) {
            int x = maxH.top().second.first;
            int y = maxH.top().second.second;

            res.push_back({x, y});
            maxH.pop();
        }

        return res;
    }
};
```

### Industry-Standard Optimization: Store Index Instead of Nested Pairs

Instead of storing `{distSq, {x, y}}`, you can store `{distSq, index}` in `priority_queue<pair<int, int>>`.

* **Benefits:** Eliminates nested `.second.first` / `.second.second` boilerplate, shrinks each heap node from 12 bytes to 8 bytes, and lets you push `points[maxH.top().second]` directly into `res`.

### Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N \log K)$ — each of the $N$ points is pushed onto a heap of size at most $K + 1$.

* **Space Complexity:** $\mathcal{O}(K)$ auxiliary space for the Max-Heap.

*(Note: Just like LC 215, this can be pushed to $\mathcal{O}(N)$ average time using **Randomized Lomuto Quickselect** partitioning on `distSq` if the interviewer demands linear time.)*

### Critical C++ Traps to Memorize

1. **Overflow Check on Squared Distance:** In LC 973, $|x|, |y| \le 10^4$, so $x^2 + y^2 \le 2 \times 10^8$, which safely fits in a 32-bit `int` (max $\approx 2.14 \times 10^9$). If a follow-up raises coordinates to $10^5$ or $10^9$, immediately upgrade to `long long`: `1LL * x * x + 1LL * y * y`.

2. **Unused Variables:** Clean up leftover variables like `int n = points.size();` when using range-based `for` loops to keep production and interview code spotless.