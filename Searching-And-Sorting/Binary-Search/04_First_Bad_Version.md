# LC 278: First Bad Version

**Pattern Trigger:** 
* A sequential range of integers (`1` to `n`).
* A boolean monotonic condition (e.g., `false, false, false, true, true`).
* Asked to find the *first* occurrence of a condition = **Lower Bound on an Answer Range**.

**The "Aha!" Pivot:**
You do not need a physical array to perform binary search. The version numbers themselves act as your `l` and `h` pointers. The provided API `isBadVersion(mid)` acts as your array lookup.

**State Variables:**
* `l = 1` (The lowest possible version)
* `h = n` (The highest possible version)

**The `while(h - l > 1)` Template Implementation:**
```cpp
int firstBadVersion(int n) {
    int l = 1, h = n; 
    
    while(h - l > 1) {
        int mid = l + (h - l) / 2; // MANDATORY to prevent integer overflow
        
        if(!isBadVersion(mid)) { // Good version (Too low)
            l = mid + 1; 
        } else {                 // Bad version (Potential answer)
            h = mid; 
        }
    }
    
    // Manual check: Interrogate l first because we want the FIRST bad version
    if(isBadVersion(l)) return l; 
    if(isBadVersion(h)) return h; 
    return -1; 
}
```

**Guardrails & Edge Cases:**
* **Integer Overflow (CRITICAL):** The constraint says $n$ can be up to $2^{31} - 1$ (the maximum 32-bit signed integer). If you do `(l + h) / 2`, the addition will overflow and crash your program. You *must* use `l + (h - l) / 2`.
* **Zero-based vs One-based:** The problem specifies versions start at `1`, so initialize `l = 1`, not `l = 0`.

**Complexity:**
* **Time:** $\mathcal{O}(\log N)$
* **Space:** $\mathcal{O}(1)$