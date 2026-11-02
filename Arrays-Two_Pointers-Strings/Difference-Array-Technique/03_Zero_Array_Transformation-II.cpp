#include <algorithm>
#include <vector>

using namespace std; 


// Optimal (DAT + BS on Queries) - log(Q) * (Q+N)
class Solution {
public:
    int n, Q; 

    bool checkWithDAT(vector<int> &nums, vector<vector<int>>& queries, int k) {
        vector<int> diff(n, 0); 

        for(int i = 0; i < k; i++) {
            int l = queries[i][0];     
            int r = queries[i][1];     
            int x = queries[i][2];     

            diff[l] += x; 
            if(r+1 < n) 
                diff[r+1] -= x; 
        }

        if((nums[0] - diff[0]) > 0) 
            return false; 

        for(int i = 1; i < n; i++) {
            diff[i] += diff[i-1]; 

            if((nums[i] - diff[i]) > 0) 
                return false; 
        }

        return true; 
    }
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        n = nums.size(); 
        Q = queries.size(); 

        auto lambda = [] (int &x) {
            return x == 0; 
        }; 

        if(all_of(nums.begin(), nums.end(), lambda)) {
            return 0; 
        } 

        int l = 0, r = Q-1; 
        int res = -1; 

        while (l <= r) {
            int mid = l + (r - l) / 2; 
            if(checkWithDAT(nums, queries, mid+1)) {
                res = mid+1; 
                r = mid - 1; 
            } else {
                l = mid + 1; 
            }
        }

        return res; 
    }
};





// Better Approach [Still Not Improved] (DAT + Straight Query Processing) 
// O(Q * Q+N)
class Solution {
public:
    int n, Q; 

    bool checkWithDAT(vector<int> &nums, vector<vector<int>>& queries, int k) {
        vector<int> diff(n, 0); 

        for(int i = 0; i < k; i++) {
            int l = queries[i][0];     
            int r = queries[i][1];     
            int x = queries[i][2];     

            diff[l] += x; 
            if(r+1 < n) 
                diff[r+1] -= x; 
        }

        if((nums[0] - diff[0]) > 0) 
            return false; 

        for(int i = 1; i < n; i++) {
            diff[i] += diff[i-1]; 

            if((nums[i] - diff[i]) > 0) 
                return false; 
        }

        return true; 
    }
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        n = nums.size(); 
        Q = queries.size(); 

        auto lambda = [] (int &x) {
            return x == 0; 
        }; 

        if(all_of(nums.begin(), nums.end(), lambda)) {
            return 0; 
        } 

        for(int i = 0; i < Q; i++) {
            if(checkWithDAT(nums, queries, i+1)) {
                return i+1; 
            }
        }

        return -1; 
    }
};



// Brute Force - O(N * Q)
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(); 
        int qCnt = 0; 

        auto allZeros = [&] (vector<int> &nums) {
            for(int i = 0; i < n; i++) {
                if(nums[i] != 0) 
                    return false; 
            } 
            return true; 
        }; 

        if(allZeros(nums))
            return 0; 

        for(auto &q : queries) {
            int l = q[0]; 
            int r = q[1]; 
            int val = q[2]; 
            qCnt++; 
            for(int i = l; i <= r; i++) {
                nums[i] = max(nums[i] - val, 0); 
                if(allZeros(nums)) 
                    return qCnt; 
            }
        }

        return -1; 
    }
};