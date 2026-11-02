#include <vector> 

using namespace std; 


// O(N) - Cyclic Sort 
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size(); 
        int i = 0; 

        while(i < n) {
            int correctIdx = nums[i] - 1; 
            if(nums[i] > 0 && nums[i] <= n && nums[i] != nums[correctIdx]) {
                swap(nums[i], nums[correctIdx]); 
            } else {
                i++; 
            }
        }

        vector<int> dups; 
        for(int j = 0; j < n; j++) {
            if(nums[j] != j+1) 
                dups.push_back(j+1); 
        }

        return dups; 
    }
};