#include<bits/stdc++.h>
using namespace std; 

// Quick Select Algo 
// TC: O(N) (Avg case)
// O(N ^ 2) -> Worst Case 
class Solution {
public:
    int partition(vector<int> &nums, int L, int R) {
        int p = nums[L];  
        int i = L+1, j = R; 

        while(i <= j) {
            if(nums[i] < p && nums[j] > p) {
                swap(nums[i], nums[j]); 
                i++; 
                j--; 
            } 

            if(nums[i] >= p) 
                i++; 
            if(nums[j] <= p)
                j--; 
        }

        swap(nums[L], nums[j]); 
        return j; 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size(); 
        int L = 0, R = n-1; 
        int pivotIdx = 0; 

        while(true) {
            pivotIdx = partition(nums, L, R); 
            if(pivotIdx == k-1) {
                break; 
            } else if(pivotIdx > k-1) {
                R = pivotIdx - 1; 
            } else {
                L = pivotIdx + 1; 
            }
        } 

        return nums[pivotIdx]; 
    }
};

// TC: O(NlogN)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if(nums.size() < k) return 0; 

        priority_queue<int> maxH(nums.begin(), nums.end()); 

        int n = nums.size(); 
        for(int i = 0; i < k-1; i++) {
            maxH.pop(); // popping top k-1th elements 
        } 

        return maxH.top();   
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if(nums.size() < k) return 0; 

        priority_queue<int, vector<int>, greater<int>> minH; 

        int n = nums.size(); 
        for(int i = 0; i < n; i++) {
            minH.push(nums[i]); 
            if(minH.size() > k) {
                minH.pop(); 
            }
        } 

        return minH.top(); 
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if(nums.size() < k) return 0; 
        sort(nums.begin(), nums.end(), greater<int>()); 
        return nums[k-1];        
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end()); 
        return nums[nums.size() - k]; 
    }
};