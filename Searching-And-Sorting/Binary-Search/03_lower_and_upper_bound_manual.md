# Lower Bound & Upper Bound (Manual Implementation)

**Pattern Trigger:**
* **Lower Bound:** Find the *first* element that is $\ge$ target.
* **Upper Bound:** Find the *first* element that is $>$ target.

### 1. The `while (h - l > 1)` Template (The CP Safe Way)
This template is heavily used in Competitive Programming because it mathematically guarantees you will never get stuck in an infinite loop, regardless of how you update `mid`.

* **The Logic:** Shrink the search space until exactly 2 elements remain (`l` and `h`). 
* **Upper vs Lower:** The *only* difference is the equality sign.
  * Lower Bound: `if (v[mid] < el)` (Push `l` past anything strictly less).
  * Upper Bound: `if (v[mid] <= el)` (Push `l` past anything less than OR equal).
* **The Manual Check:** Because the loop stops early, you must check the two remaining suspects. 
  ```cpp
  // Lower Bound Check
  if(v[l] >= el) return l; 
  if(v[h] >= el) return h; 
  return -1; // Target is larger than the max element
  ```

### 2. The `while (l < h)` Template (The Standard Way)
* **The Logic:** Shrink the search space until `l` and `h` converge on the exact answer.
* **The Trap:** When updating bounds, `l = mid + 1` is safe, but `h = mid` can cause an infinite loop if not careful. 
* **The Check:** Once the loop finishes, `l` is your only answer. You just need a single verification:
  ```cpp
  if(v[l] >= el) return l;
  return -1;
  ```