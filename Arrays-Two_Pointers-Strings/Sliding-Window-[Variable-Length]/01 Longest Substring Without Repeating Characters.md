# LC 3: Longest Substring Without Repeating Characters

**Pattern Trigger:** "Longest substring" governed by a constraint (no repeats) = Variable Sliding Window.

**State Variables:** 
- `left`, `right` pointers
- `maxLen` 
- `unordered_set<char> window`

**The "Aha!" Pivot:** 
The window is valid as long as characters are unique. When `s[right]` is already in the set, the window is broken. Use an inner `while` loop to `erase(s[left])` and increment `left` until the duplicate is gone. Only update `maxLen` after the `while` loop when the window is guaranteed valid again.

**Edge Cases to Memorize:**
- `""` -> 0 (Initialize `maxLen = 0` to handle naturally)
- `"bbbbb"` -> 1 (Tests aggressive left-pointer shrinking)

**Complexity:** Time `O(N)`, Space `O(min(N, 26))`