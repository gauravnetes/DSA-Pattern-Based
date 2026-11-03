#include<bits/stdc++.h>
using namespace std; 

// findPivot() executes in O(logN) time 
// TC: O(logN) + O(logN) + O(logN) => O(3logN) -> O(logN) 
// SC: O(1)
class Solution {
public:
    int bS(vector<int> &nums, int l, int r, int target) {
        while(l <= r) {
            int mid = l + (r - l) / 2; 
            if(nums[mid] == target) 
                return mid; 
            else if(nums[mid] < target) 
                l = mid + 1; 
            else 
                r = mid - 1; 
        }
        return -1; 
    }

    int findPivot(vector<int> &nums, int n) {
        int l = 0, r = n-1; 
        while(l < r) {
            int mid = l + (r - l) / 2; 
            if(nums[mid] > nums[r]) 
                l = mid + 1; 
            else 
                r = mid; 
        }
        return r; 
    }

    int search(vector<int>& nums, int target) {
        int n = nums.size(); 
        int pivotIdx = findPivot(nums, n); 

        int targetIdx = bS(nums, 0, pivotIdx - 1, target); 
        if(targetIdx != -1) 
            return targetIdx; 
        
        targetIdx = bS(nums, pivotIdx, n-1, target); 
        return targetIdx; 
    }
};

// O(N) Solution 
// Finding the Pivot Idx takes - O(N) through a loop pass 
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