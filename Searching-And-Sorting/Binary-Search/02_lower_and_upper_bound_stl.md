# C++ STL: Lower Bound & Upper Bound

The C++ Standard Template Library provides highly optimized, built-in binary search functions. They return **iterators** (or pointers) rather than indices.

### 1. Vectors (Returns Iterator)
```cpp
auto it = lower_bound(a.begin(), a.end(), target);

// 1. Check if found (Did it fall off the edge?)
if (it == a.end()) {
    cout << "Not Found"; 
} else {
    // 2. Dereference to get the value
    cout << *it; 
    
    // 3. Get the 0-based index using pointer arithmetic
    int index = it - a.begin(); 
}
```

### 2. C-Style Arrays (Returns Pointer)
```cpp
int *ptr = lower_bound(a, a + n, target);

// 1. Check if found
if (ptr == (a + n)) {
    cout << "Not Found";
} else {
    cout << *ptr; // The value
    int index = ptr - a; // The 0-based index
}
```

### 3. Sets and Maps (THE CRITICAL TRAP)
**DO NOT DO THIS:** `lower_bound(st.begin(), st.end(), target);`
* **Why it's bad:** `std::set` does not have random access iterators (like vectors do). Using the generic `std::lower_bound` algorithm on a set forces it to step through elements one by one, degrading the time complexity from $\mathcal{O}(\log N)$ to $\mathcal{O}(N)$!

**DO THIS INSTEAD:** `st.lower_bound(target);`
* **Why it's good:** Sets and Maps have their own built-in member functions that traverse their internal Red-Black Tree structures, keeping the search strictly at $\mathcal{O}(\log N)$.