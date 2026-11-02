# LC 268: Missing Number

**Pattern Trigger:** Array elements in a predictable range like `[0, n]` or `[1, n]`, asked to find a "missing" or "duplicate" number = Cyclic Sort.

**State Variables:**
- `i` (current index pointer)
- `n` (size of the array / the out-of-bounds value)
- `correctIdx` (where the current number belongs)

**The "Aha!" Pivot:**
Every number belongs at the index matching its value (for a `[0, n]` range, `correctIdx = nums[i]`). 
While scanning, if `nums[i]` is within bounds (`< n`) and not at its correct index, swap it with the number at `correctIdx`. **Do not increment `i` after a swap**—re-evaluate the new number that just arrived.
The out-of-bounds number (`n`) acts as a wandering placeholder. It gets constantly evicted by valid numbers until it is forced into the empty slot left by the missing number. A final linear scan finds the missing number where `nums[j] != j`.

**Edge Cases to Memorize:**
- **The missing number is `n`:** If the array is perfectly sorted from `0` to `n-1`, the final loop will finish without finding a mismatch. Simply return `n` as the fallback.
- **Index offset:** For `[0, n]` ranges, `correctIdx = nums[i]`. For `[1, n]` ranges, it is `correctIdx = nums[i] - 1`.

**Complexity:**
- **Time:** $\mathcal{O}(N)$ (Each element is placed in its correct position at most once).
- **Space:** $\mathcal{O}(1)$ (In-place modification).