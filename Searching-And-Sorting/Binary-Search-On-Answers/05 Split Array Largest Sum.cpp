#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    int solve(vector<int> &nums, int sum) {
        int subArrCnt = 1; 
        int currSubArrSum = 0; 

        for(int i = 0; i < nums.size(); i++) {
            if(currSubArrSum + nums[i] <= sum) {
                currSubArrSum += nums[i]; 
            } else {
                subArrCnt++; 
                currSubArrSum = nums[i]; 
            }
        }
        return subArrCnt; 
    }

    int splitArray(vector<int>& nums, int k) {
        int n = nums.size(); 

        int l = *max_element(nums.begin(), nums.end()); 
        int r = accumulate(nums.begin(), nums.end(), 0); 

        int ans = 0; 

        while(l <= r) {
            int mid = l + (r - l) / 2; 
            int subArrCnt = solve(nums, mid); 

            if(subArrCnt > k) {
                l = mid + 1; 
            } else {
                ans = mid; 
                r = mid - 1; 
            }
        }
        return ans; 
    }
};