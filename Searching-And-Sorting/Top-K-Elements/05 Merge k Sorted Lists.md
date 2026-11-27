# LC 23: Merge k Sorted Lists (K-Way Merge)

**Pattern Trigger:**

* You are given $K$ individually sorted linked lists, arrays, or streams and need to merge them into a single sorted sequence.
* Naive pairwise merging or dumping all $N$ elements into an array and sorting takes $\mathcal{O}(N \cdot K)$ or $\mathcal{O}(N \log N)$ time. A Min-Heap of size $K$ reduces this to $\mathcal{O}(N \log K)$.

### Core Concept: The K-Way Merge Frontier

Instead of comparing all $K$ list heads linearly at every step ($\mathcal{O}(K)$ per node), maintain a **Min-Heap** holding only the current front node of each non-empty list (at most $K$ nodes at any time):

1. Push the head of every non-empty list into the Min-Heap.
2. Pop the smallest node (`minH.top()`) and attach it to your result list.
3. If that popped node has a `next` node, push `currNode->next` into the Min-Heap to replenish the frontier.
4. Repeat until the heap is empty.

### Custom Lambda Comparator for `priority_queue`

Because the heap stores raw pointers (`ListNode*`), a default `priority_queue` would compare **memory addresses** instead of node values. You must supply a custom comparator:

* **Why `>` creates a Min-Heap:** In C++, `std::priority_queue` puts the element that returns `true` for "lower priority" deeper in the tree. Returning `node1->val > node2->val` tells the heap that larger values have lower priority, keeping the **smallest** value at `.top()`.
* **Syntax:** Pass `decltype(lambda)` as the third template argument and pass `(lambda)` to the constructor.

### Code Template (Your Approach, Fixed & Cleaned)

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Min-Heap comparator: larger value = lower priority
        auto lambda = [](const ListNode* node1, const ListNode* node2) {
            return node1->val > node2->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(lambda)> minH(lambda);

        // 1. Seed the heap with the head of every non-empty list
        for (ListNode* node : lists) {
            if (node) {
                minH.push(node);
            }
        }

        // Guard against empty input or a vector of empty lists: [ [], [] ]
        if (minH.empty()) {
            return nullptr;
        }

        // 2. Establish the head of the merged list
        ListNode* head = minH.top();
        minH.pop();

        if (head->next) {
            minH.push(head->next);
        }

        // 3. Greedily attach the next smallest node until the heap is drained
        ListNode* tail = head;
        while (!minH.empty()) {
            ListNode* currNode = minH.top();
            minH.pop();

            tail->next = currNode;
            tail = tail->next;

            if (currNode->next) {
                minH.push(currNode->next);
            }
        }

        return head;
    }
};
```

### Complexity Analysis

Let $N$ be the total number of nodes across all $K$ lists.

* **Time Complexity:** $\mathcal{O}(N \log K)$ — Every node is pushed and popped from the heap exactly once, and the heap never holds more than $K$ nodes.
* **Space Complexity:** $\mathcal{O}(K)$ auxiliary space for the Min-Heap (nodes are re-linked in-place without allocating new `ListNode` objects).

### Critical C++ Traps to Memorize

1. **Null-Pointer Guard Before `.push()`:** Always check `if (node)` and `if (currNode->next)` before pushing into the heap. Pushing a `nullptr` causes an immediate Segmentation Fault as soon as the comparator evaluates `node1->val`.
2. **Consistent Naming & Modern Nulls:** Avoid switching heap names mid-function (`minH` vs. `pq`), and prefer `nullptr` over `NULL` in modern C++.
3. **Optional Refactor (Stack Dummy Node):** If you want to eliminate the separate `head` setup block and `if (minH.empty())` guard, declare `ListNode dummy(0); ListNode* tail = &dummy;` on the stack (zero heap allocation / zero memory leak) and return `dummy.next` after the single `while` loop.