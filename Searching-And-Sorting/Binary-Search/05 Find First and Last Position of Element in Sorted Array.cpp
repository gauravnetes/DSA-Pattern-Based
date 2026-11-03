#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    int n; 
    int lb(vector<int> &nums, int target) {
        int l = 0, h = n-1; 

        while(h - l > 1) {
            int mid = l + (h - l) / 2; 
            if(nums[mid] < target) {
                l = mid + 1; 
            } else {
                h = mid; 
            }
        }

        if(nums[l] >= target) 
            return l; 
        if(nums[h] >= target) 
            return h; 
        return -1; 
    }

    int ub(vector<int> &nums, int target) {
        int l = 0, h = n-1; 

        while(h - l > 1) {
            int mid = l + (h - l) / 2; 
            if(nums[mid] <= target) {
                l = mid + 1; 
            } else {
                h = mid; 
            }
        }

        if(nums[l] > target) 
            return l; 
        if(nums[h] > target) 
            return h; 
        return n; 
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        n = nums.size(); 

        if(n == 0) 
            return {-1, -1}; 

        int lbIdx = lb(nums, target); 

        if(lbIdx == -1 || nums[lbIdx] != target) 
            return {-1, -1}; 

        int ubIdx = ub(nums, target);

        return {lbIdx, ubIdx-1};     
    }
};