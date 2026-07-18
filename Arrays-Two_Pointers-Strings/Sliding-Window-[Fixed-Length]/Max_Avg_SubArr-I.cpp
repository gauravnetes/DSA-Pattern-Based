#include <vector>

using namespace std; 

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size(); 

        double maxSum = INT_MIN; 
        double currSum = 0; 

        int i = 0, j = 0; 

        while(j < n) {
            currSum += nums[j]; 

            if(j-i+1 == k) {
                maxSum = max(maxSum, currSum); 
                currSum -= nums[i]; 
                i++; 
            }

            j++; 
        }

        return maxSum == INT_MIN ? 0 : (maxSum / k); 
    }
};