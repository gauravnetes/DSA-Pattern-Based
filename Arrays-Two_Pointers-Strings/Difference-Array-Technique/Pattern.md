# Pattern: Difference Array Technique (DAT)

**Pattern Trigger:** "Add $V$ to all elements in range $[L, R]$", multiple range updates applied all at once without querying in between.

**State Variables:** 
- `vector<long long> diff(n, 0)` (Use `long long` to prevent overflow during accumulation).

**The "Aha!" Pivot:** 
Instead of a brute-force $O(N)$ loop for each update, record only the *change in slope*. 
1. Add $V$ at `diff[L]` (starts the effect).
2. Subtract $V$ at `diff[R + 1]` (terminates the effect). 
Run a single cumulative sum (prefix sum) at the very end to reconstruct the final array.

**Edge Cases to Memorize:**
- Always check `if (R + 1 < n)` before subtracting to avoid Out-Of-Bounds errors.
- Massive additions can cause integer overflow; use `long long` for the prefix sum variable.

**Complexity:** 
- **Time:** $O(1)$ per update, $O(N)$ for the final cumulative sum reconstruction. 
- **Space:** $O(N)$ for the difference array.

**Trade-off (vs. Segment Tree):**
Use DAT when all updates happen *before* you need to read the data. Use Segment Trees ($O(\log N)$ updates) only if you need to interleave updates and queries dynamically.