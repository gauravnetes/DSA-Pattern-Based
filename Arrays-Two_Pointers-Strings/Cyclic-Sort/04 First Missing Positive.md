# LC 41: First Missing Positive

**Pattern Trigger:** Unsorted array, asked for the "smallest positive integer missing", $\mathcal{O}(N)$ time & $\mathcal{O}(1)$ space constraint = Cyclic Sort (Boss Level).

**State Variables:**

* `i` (current pointer)

* `n` (array size, acts as the absolute maximum possible answer)

**The "Aha!" Pivot:**
An array of size $N$ can only hold a maximum sequence of $1$ to $N$. Any number $\le 0$ or $> N$ is completely useless to our goal.
Treat the array as a `1` to $N$ range where `correctIdx = nums[i] - 1`.
The bounds check `nums[i] > 0 && nums[i] <= n` naturally filters out all negatives, zeros, and massive numbers. They act as wandering placeholders and are continually displaced until the valid numbers ($1$ to $N$) settle into their correct indices.

**Edge Cases to Memorize:**

* **Integer Underflow:** If `nums[i]` is `INT_MIN`, `nums[i] - 1` will underflow standard integers. Using `long long` for `correctIdx` is a brilliant, defensive move to prevent this crash.

* **Perfect Sequence:** If the array is perfectly `[1, 2, 3]`, the loop finishes with no mismatches. Always return `n + 1` as the fallback outside the loop.

**Complexity:**

* **Time:** $\mathcal{O}(N)$ (Even with the inner `while` logic, each number is placed at most once).

* **Space:** $\mathcal{O}(1)$ (In-place sorting).