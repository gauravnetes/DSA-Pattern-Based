# Master Pattern: Binary Search (LC 704)

**Pattern Trigger:**
* Array is **sorted** (or has a monotonic property).
* Asked to find a target, or a boundary (first/last occurrence).
* Strict $\mathcal{O}(\log N)$ time complexity requirement.

**The "Aha!" Pivot:**
Instead of scanning element by element, calculate the middle point and eliminate half of the remaining search space in a single check. The calculation `mid = l + (r - l) / 2` is mandatory to prevent integer overflow that can occur with `(l + r) / 2`.

### 1. Iterative Template (Gold Standard)
**Complexity:** Time $\mathcal{O}(\log N)$ | Space $\mathcal{O}(1)$

* Use a `while(l <= r)` loop. 
* If `nums[mid] == target`, return `mid`.
* If `nums[mid] < target`, the target must be to the right: `l = mid + 1`.
* If `nums[mid] > target`, the target must be to the left: `r = mid - 1`.
* If the loop terminates without returning, the target is not in the array (`return -1`).

### 2. Recursive Template
**Complexity:** Time $\mathcal{O}(\log N)$ | Space $\mathcal{O}(\log N)$

* The base case is the inverse of the iterative loop condition: `if (l > r) return -1;`.
* Recursive calls replace the pointer updates. 
* **Critical Trap:** You must `return` the recursive calls (e.g., `return bS(...)`), otherwise the found index will not propagate back up the call stack.
* While mathematically elegant, this uses $\mathcal{O}(\log N)$ auxiliary space due to the call stack frames. In interviews, the iterative $\mathcal{O}(1)$ space approach is almost always preferred.