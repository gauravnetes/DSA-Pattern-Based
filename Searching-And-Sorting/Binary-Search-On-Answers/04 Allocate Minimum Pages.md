# Allocate Minimum Number of Pages / Split Array Largest Sum (LC 410)

**Pattern Trigger:**

* The problem asks to **"Minimize the Maximum"** (e.g., minimize the maximum number of pages assigned to a single student, minimize the largest sum of any subarray).
* The elements must be allocated in a **contiguous** manner (subarrays, not subsequences).
* Validating a target maximum sum takes $\mathcal{O}(N)$ time, but calculating it directly is mathematically difficult.

### The Search Space (Boundaries)

* **Minimum Possible Answer (`l`):** The absolute smallest maximum capacity you can have is the size of the single largest book. You cannot split a book between students. (`*max_element`)
* **Maximum Possible Answer (`r`):** If there is only 1 student, they must read all the books. The maximum possible answer is the sum of the entire array. (`std::accumulate`)

### The State-First Framework (Contiguous Allocation)

When grouping contiguous elements, always structure your conditional logic by checking for the violation *first*.

1. **The Violation Trigger:** At what exact moment does the current student's workload become illegal?
   * *Logic:* If giving them the current book pushes their total pages strictly over the allowed limit (`mid`).
   * *Code:* `if (currStudentPages + arr[i] > pages)`

2. **The State Reset:** What happens when the limit is breached?
   * *Logic:* We must bring in a new student (`students++`). The current book doesn't disappear; it becomes the first book for this *new* student.
   * *Code:* `currStudentPages = arr[i];`

3. **The Happy Path:** What if there is no violation?
   * *Logic:* Keep piling books onto the current student.
   * *Code:* `else { currStudentPages += arr[i]; }`

### Code Template

```cpp
class Solution {
public:
    // Helper function using State-First logic
    int solve(const vector<int> &arr, long long pages) {
        int students = 1; 
        long long currStudentPages = 0; // Use long long to prevent accumulation overflow
        
        for(int i = 0; i < arr.size(); i++) {
            // 1. Violation
            if(currStudentPages + arr[i] > pages) {
                students++;                // 2a. Reset State (new student)
                currStudentPages = arr[i]; // 2b. Survive (give book to new student)
            } else {
                // 3. Happy Path
                currStudentPages += arr[i]; 
            }
        }
        return students; 
    }
    
    long long findPages(vector<int> &arr, int m) {
        int n = arr.size(); 
        
        // Impossible to allocate if there are more students than books
        if(n < m) 
            return -1; 
            
        long long l = *max_element(arr.begin(), arr.end()); 
        
        // CRITICAL: 0LL forces a 64-bit integer sum. 
        // Using '0' here will cause a silent integer overflow on large arrays!
        long long r = accumulate(arr.begin(), arr.end(), 0LL); 
        long long ans = 0; 
        
        while(l <= r) {
            long long mid = l + (r - l) / 2; 
            
            int studentsCnt = solve(arr, mid); 
            
            if(studentsCnt > m) {
                // We used too many students. We must increase the page limit per student.
                l = mid + 1; 
            } else {
                // Valid distribution! Lock it in, but try to find a smaller maximum limit.
                ans = mid;   
                r = mid - 1; 
            }
        }
        
        return ans; 
    }
};
```

### Critical C++ Traps to Memorize

1. **The `0LL` Accumulate Trap:** This is the most common reason for a Wrong Answer (WA) on hidden test cases with massive inputs (e.g., an array of $10^5$ elements, each being $10^4$). `accumulate(..., 0)` defaults to a 32-bit `int`, overflowing at $2.14 \times 10^9$. Always type `0LL`.
2. **Propagating `long long`:** If your `r` boundary requires a 64-bit integer, your `mid` will also be a 64-bit integer. Therefore, the parameter `pages` in your helper function, as well as the internal `currStudentPages` accumulator, **must** also be `long long`. 