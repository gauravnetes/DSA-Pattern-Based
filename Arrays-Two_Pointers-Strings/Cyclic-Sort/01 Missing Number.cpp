#include <vector> 
#include <algorithm> 

using namespace std; 


// OPTIMAL: Cyclic Sort 
// TC: O(N + N) -> O(N) 
// SC: O(1) 
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size(); 
        int i = 0; 

        while(i < n) {
            int correctIdx = nums[i]; 
            if(nums[i] < n && nums[i] != nums[correctIdx]) {
                swap(nums[i], nums[correctIdx]); 
            } else {
                i++; 
            }
        }

        for(int j = 0; j < n; j++) {
            if(nums[j] != j)
                return j; 
        }

        return n; 
    }
};

// OPTIMAL TRICK: SUM OF N NUMBERS 
// TC: O(N) 
// SC: O(1) 
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size(); 
        // sum upto n numbers: n * (n + 1) / 2 
        int sumUptoN = (n * (n + 1)) / 2; 
        int sum = 0; 
        for(int i = 0; i < n; i++) {
            sum += nums[i]; 
        }

        return sumUptoN - sum; 
    }
};

// BRUTE: Sorting
// TC: O(NlogN) 
// SC: O(1) 
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size(); 
        sort(nums.begin(), nums.end()); // 0, 1, 3

        if(nums[0] != 0) 
            return 0; 
 
        if(nums[n-1] != n) 
            return n; 

        for(int i = 1; i < n; i++) {
            if(nums[i] != nums[i-1]+1) {
                return nums[i-1] + 1; 
            }
        }

        return -1; 
    }
};