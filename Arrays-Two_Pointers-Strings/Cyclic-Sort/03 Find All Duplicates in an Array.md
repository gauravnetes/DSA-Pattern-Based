# LC 442: Find All Duplicates in an Array

**Pattern Trigger:** Array of size $N$ with elements in range $[1, N]$, some appearing twice. "Find all duplicates" = Cyclic Sort.

**State Variables:**

* `i` (current pointer)

* `n` (array size)

* `dups` (result array)

**The "Aha!" Pivot:**
The sorting logic is mathematically identical to LC 448 (Find Disappeared Numbers).
Because elements are in the range `1` to $N$, `correctIdx = nums[i] - 1`.
The duplicate check `nums[i] != nums[correctIdx]` prevents infinite loops and forces the extra duplicates to become stranded in the indices of the missing numbers.

**Edge Cases to Memorize:**

* **The Extraction Trap (CRITICAL):** After the array is sorted, scanning for mismatches (`nums[j] != j + 1`) reveals two things:

  1. `j + 1` is the **missing** number.

  2. `nums[j]` is the **duplicate** number sitting in the wrong slot.
     **Make sure you `push_back(nums[j])`, not `j + 1`!**

**Complexity:**

* **Time:** $\mathcal{O}(N)$

* **Space:** $\mathcal{O}(1)$ (excluding the returned array)