# Master Pattern: Cyclic Sort

**Pattern Trigger:** 
- Array of size $N$ with elements in a predictable, continuous range ($1$ to $N$, $0$ to $N$).
- Asked to find "missing", "duplicate", or "smallest positive" numbers.
- Strict $\mathcal{O}(N)$ time and $\mathcal{O}(1)$ space constraints.

**State Variables:**
- `int i = 0` (The stationary scanning pointer)
- `int n = nums.size()` (Array bounds)
- `correctIdx` (The calculated mathematical home for the current number)

**The "Aha!" Pivot:**
Every valid number dictates its own index. You are a mailman putting letters in the right boxes. 
You must use a `while` loop because after you swap a number into its correct place, the *new* number you just pulled into index `i` must be evaluated immediately. You only increment `i` when no more productive swaps can be made at the current slot.

**The Skeleton Template:**
```cpp
int i = 0;
while (i < n) {
    // 1. Calculate target (0-based = nums[i], 1-based = nums[i] - 1)
    int correctIdx = nums[i] - 1; 

    // 2. Bounds Check AND Duplicate Guard
    if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[correctIdx]) {
        swap(nums[i], nums[correctIdx]); // Do NOT increment 'i' here
    } else {
        i++; // Move on only if placed, out-of-bounds, or duplicate
    }
}
```

**Guardrails & Edge Cases:**
- **0-based vs 1-based:** `[0, N]` uses `correctIdx = nums[i]`. `[1, N]` uses `correctIdx = nums[i] - 1`. Getting this wrong causes instant Out-Of-Bounds crashes.
- **The Infinite Loop Trap:** Never swap blindly. You *must* check `nums[i] != nums[correctIdx]` to ensure you aren't swapping two identical duplicates forever.
- **The Wandering Placeholder:** Any number outside the target range (negatives, $>N$) is ignored during the swap phase. Valid numbers will aggressively evict them, forcing them into the slots belonging to the actual missing numbers.

**The Reveal Scan:**
After sorting, a single linear `for` loop checking `nums[j] != expected_value` reveals everything:
- `expected_value` is the **missing** number.
- `nums[j]` is the stranded **duplicate** number.