# LC 215: Kth Largest Element in an Array

**Pattern Trigger:**

* The problem asks for the "Kth largest", "Kth smallest", or "Top K" elements in a dataset.
* You need a continuously sorted stream, or you need to avoid fully sorting an entire array $\mathcal{O}(N \log N)$ when you only care about a small subset of the data.

---

### The Core Concept: What are you throwing away?

When using heaps, the most important question to ask is: **"What does `.pop()` destroy?"**

#### 1. The Min-Heap Strategy (Size Restricted to K)
* **What it pops:** The absolute *smallest* element currently in the heap.
* **The Logic:** By keeping the heap size strictly at $K$, every time it grows to $K+1$, you pop the smallest number. By continuously throwing away the smallest numbers, the heap naturally traps the $K$ **largest** numbers by the time the loop ends. The top of the heap is the minimum of those $K$ largest numbers, which is your exact answer.
* **Complexity:** $\mathcal{O}(N \log K)$ time, $\mathcal{O}(K)$ space.

#### 2. The Max-Heap Strategy (Full Size)
* **What it pops:** The absolute *largest* element currently in the heap.
* **The Logic:** If you restrict a Max-Heap to size $K$, you will accidentally throw away the largest numbers in the array! Instead, you must put **all** $N$ elements into the heap, let the largest float to the top, and then manually pop $K - 1$ times to reach the target.
* **Complexity:** $\mathcal{O}(N + K \log N)$ time, $\mathcal{O}(N)$ space.

---

### Code Templates

#### Approach 1: Min-Heap (Best when K is small)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // C++ Min-Heap declaration
        priority_queue<int, vector<int>, greater<int>> minH; 

        for(int num : nums) {
            minH.push(num); 
            // Restrict size to K, throwing away the smallest elements
            if(minH.size() > k) {
                minH.pop(); 
            }
        } 

        // The top is the smallest of the K largest elements
        return minH.top(); 
    }
};
```

#### Approach 2: Max-Heap (C++ Optimization Trick)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // CRITICAL TRICK: Passing iterators directly to the constructor 
        // runs the internal std::make_heap algorithm, building the heap in 
        // strict O(N) time instead of O(N log N) from manual pushing.
        priority_queue<int> maxH(nums.begin(), nums.end()); 

        // Throw away the absolute largest elements K-1 times
        for(int i = 0; i < k - 1; i++) {
            maxH.pop(); 
        }

        return maxH.top();   
    }
};
```

### Key C++ Execution Traps
1. **The $\mathcal{O}(N)$ Heapify Trap:** Never write a `for` loop to manually `.push()` $N$ elements into a heap if you already have the full array. Always pass `(nums.begin(), nums.end())` to the `priority_queue` constructor. It changes the build time from $\mathcal{O}(N \log N)$ down to $\mathcal{O}(N)$.
2. **Min-Heap Syntax:** `priority_queue<int>` defaults to a Max-Heap in C++. You must memorize the verbose `priority_queue<int, vector<int>, greater<int>>` to summon a Min-Heap.