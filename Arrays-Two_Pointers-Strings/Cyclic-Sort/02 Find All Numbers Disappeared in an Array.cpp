#include <vector> 

using namespace std; 

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size(); 
        int i = 0;

        while(i < n) {
            int correctIdx = nums[i] - 1; 
            if(nums[i] <= n && nums[i] != nums[correctIdx]) {
                swap(nums[i], nums[correctIdx]); 
            } else {
                i++; 
            }
        }

        vector<int> missingEls; 
        for(int j = 0; j < n; j++) {
            if(nums[j] != j+1) 
                missingEls.push_back(j+1); 
        }

        return missingEls; 
    }
};