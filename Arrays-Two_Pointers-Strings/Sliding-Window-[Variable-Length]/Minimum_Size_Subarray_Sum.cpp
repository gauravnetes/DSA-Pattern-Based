#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std; 

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(); 

        int minLen = INT_MAX; 
        int i = 0, j = 0; 
        int sum = 0; 

        while(j < n) {
            sum += nums[j]; 
            
            while (sum >= target) {
                minLen = min(minLen, j-i+1); 
                sum -= nums[i]; 
                i++; 
            }

            j++; 
        }
        return minLen == INT_MAX ? 0 : minLen; 
    }
};