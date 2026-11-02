#include <vector>
#include <climits>

using namespace std; 

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(); 

        int i = 0, j = 0;  
        int flipCnt = 0;
        int maxLen = 0; 

        while(j < n) {
            if(nums[j] == 0) {
                flipCnt++; 
            }

            if(flipCnt > k) {
                if(nums[i] == 0) {
                    flipCnt--; 
                }
                i++; 
            }

            maxLen = max(maxLen, j-i+1); 
            j++; 
        }
  
        return maxLen; 
    }
};