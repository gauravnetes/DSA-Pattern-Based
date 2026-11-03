#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size(); 

        int l = 0, r = n-1; 
        int resIdx = 0; 

        while(l <= r) {
            while(l < r && nums[l] == nums[l+1]) l++; 
            while(l < r && nums[r] == nums[r-1]) r--; 
            
            int mid = l + (r - l) / 2; 
            if(nums[mid] < nums[resIdx])
                resIdx = mid; 
            if(nums[mid] > nums[r])
                l = mid+1; 
            else 
                r = mid - 1; 
        }

        return nums[resIdx]; 
    }
};