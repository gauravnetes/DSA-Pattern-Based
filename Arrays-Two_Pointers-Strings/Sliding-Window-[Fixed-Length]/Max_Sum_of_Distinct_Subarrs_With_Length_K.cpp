#include <unordered_set>
#include <vector>

using namespace std; 

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(); 

        int i = 0, j = 0; 
        long long sum = 0; 
        long long res = INT_MIN; 

        unordered_set<int> st; 

        while(j < n) {
            sum += nums[j]; 
            while(st.find(nums[j]) != st.end()) {
                st.erase(nums[i]); 
                sum -= nums[i]; 
                i++; 
            }

            if(j-i+1 == k) {
                res = max(sum, res); 
                sum -= nums[i]; 
                st.erase(nums[i]); 
                i++; 
            } 

            st.insert(nums[j]); 
            j++;
        }

        return res == INT_MIN ? 0 : res; 
    }
};