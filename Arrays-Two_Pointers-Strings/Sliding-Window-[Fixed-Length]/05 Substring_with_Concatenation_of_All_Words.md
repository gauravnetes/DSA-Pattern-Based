# LC 30: Substring with Concatenation of All Words

**Pattern Trigger:** "Concatenation of All Words" or finding permutations of fixed-length strings = Sliding Window (Fixed) with Hashmap.

**State Variables:** 
- `unordered_map<string, int> mp` (Target word frequencies)
- `unordered_map<string, int> seen` (Current window frequencies)
- `count` (Number of valid words currently matched)
- `left` (Window start boundary)
- `wordLen` (Length of a single word)

**The "Aha!" Pivot:** 
Treat each word chunk exactly like a single character in a standard sliding window. 
*   **The Alignment Trick:** Because words can start at any index, you must run `wordLen` completely separate sliding windows. Use an outer loop from `0` to `wordLen - 1`, and step your inner `j` pointer by `wordLen`.
*   **Invalid Word:** If the chunk is not in `mp`, completely clear `seen`, reset `count = 0`, and move `left = j + wordLen`.
*   **Over-matched Word:** If `seen[word] > mp[word]`, shrink the window from the `left` by `wordLen` chunks (decrementing `seen` and `count`) until the excess word is evicted. 

**Edge Cases to Memorize:**
- `s.length() < total_words_length` -> Return empty array immediately.
- Overlapping valid words that require aggressive left-shrinking to re-validate the window.

**Complexity:** 
- **Time:** $O(N \times \text{wordLen})$
- **Space:** $O(K)$ where $K$ is the number of unique words in the array.