#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int maxVal = *max_element(nums.begin(), nums.end()) + k; 

        vector<int> diff(maxVal + 2, 0); 
        unordered_map<int, int> freq; 

        for(int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++; 

            int l = max(nums[i]-k, 0); 
            int r = min(nums[i]+k, maxVal); 

            diff[l]++; 
            diff[r+1]--; 
        }

        int res = 1; 
        for(int target = 0; target <= maxVal; target++) {
            diff[target] += (target > 0 ? diff[target-1] : 0); 
            int targetFreq = freq[target]; 
            int needConversion = diff[target] - targetFreq; 
            int maxPossibleFreq = min(needConversion, numOperations); 
            res = max(res, maxPossibleFreq + targetFreq); 
        }

        return res; 
    }
};