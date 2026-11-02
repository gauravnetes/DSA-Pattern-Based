# LC 448: Find All Numbers Disappeared in an Array

**Pattern Trigger:** Array of size $N$ with elements in range $[1, N]$, some appearing twice and others zero times. "Find all disappeared" = Cyclic Sort.

**State Variables:** 
- `i` (current pointer)
- `n` (array size)
- `missingEls` (result array)

**The "Aha!" Pivot:** 
This is a `1` to $N$ range, so a number `val` belongs at index `val - 1`. 
The core duplicate check `nums[i] != nums[correctIdx]` is the hero here. When the algorithm encounters a duplicate number, it checks its target index. If the target index is already occupied by the correct number, the condition fails, skipping the swap. The extra duplicate simply gets stranded in a "wrong" index, acting as a placeholder for the number that actually disappeared. 

**Edge Cases to Memorize:**
- Unlike the base missing number problem, there is no single out-of-bounds number (`n`) wandering around. Instead, the *duplicates* act as the wandering placeholders that get trapped in the empty slots.
- When scanning at the end, remember to push `j + 1` (the expected 1-based number) into your result, not just `j`.

**Complexity:** 
- **Time:** $\mathcal{O}(N)$ 
- **Space:** $\mathcal{O}(1)$ (excluding the returned array)