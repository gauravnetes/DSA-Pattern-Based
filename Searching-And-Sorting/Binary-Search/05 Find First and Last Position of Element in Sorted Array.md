# LC 34: Find First and Last Position of Element in Sorted Array

**Pattern Trigger:**

* Sorted array with duplicate elements.
* Asked to find the "range", "frequency", or "first and last occurrence" of a target.
* $\mathcal{O}(\log N)$ time constraint = **Lower Bound + Upper Bound**.

**The "Aha!" Pivot:**
You don't need a custom binary search algorithm. You can build the answer using the standard bounding functions:
1. The **First Occurrence** is exactly the **Lower Bound** (the first element $\ge$ target).
2. The **Last Occurrence** is exactly **Upper Bound - 1** (one step to the left of the first element $>$ target).

**The Two-Part Strategy:**

* **Step 1:** Find the Lower Bound index (`lbIdx`).
* **Step 2:** Check if the element actually exists. If `lbIdx == -1` or `nums[lbIdx] != target`, return `{-1, -1}` immediately.
* **Step 3:** Find the Upper Bound index (`ubIdx`).
* **Step 4:** Return `{lbIdx, ubIdx - 1}`.

**Critical Traps to Memorize:**

* **The Upper Bound Condition Trap:** Inside your manual `ub` checks, you *must* check `if (nums[l] > target)`, strictly greater than! If you use `>=`, your upper bound devolves into a lower bound, and you will fail on arrays like `[2, 2]`.
* **The Empty Array Crash:** Always add a fast-exit `if (n == 0) return {-1, -1};` at the top. If `n = 0`, `n-1` becomes `-1`, breaking the pointer logic and causing Out-Of-Bounds runtime errors.
* **The Pass-By-Value TLE:** Always pass `vector<int> &nums` into your helper functions by reference. Passing by value creates a full copy of the array on every call, skyrocketing your Time and Space complexity to $\mathcal{O}(N)$.

**Complexity:**

* **Time:** $\mathcal{O}(\log N)$ (Two separate logarithmic binary searches).
* **Space:** $\mathcal{O}(1)$ (Using iterative bounding templates).