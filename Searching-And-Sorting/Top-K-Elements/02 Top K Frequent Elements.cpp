#include<bits/stdc++.h>
using namespace std; 


// Bucket Sort Approach 
// TC: O(N) 
// SC: O(N)
class Solution {
public:
    typedef pair<int, int> P; 

    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size(); 
        unordered_map<int, int> mp;

        for(int i = 0; i < n; i++) {
            mp[nums[i]]++; 
        }

        vector<vector<int>> bucket(n+1, vector<int>({})); 
        for(auto &it : mp) {
            bucket[it.second].push_back(it.first); 
        }

        vector<int> res; 
        for(int i = n; i >= 0; i--) {
            while(!bucket[i].empty() && k > 0) {
                res.push_back(bucket[i].back()); 
                bucket[i].pop_back(); 
                k--; 
            }
        }

        return res; 
    }
};

// Max Heap Approach
class Solution {
public:
    typedef pair<int, int> P; 

    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size(); 
        unordered_map<int, int> mp;

        for(int i = 0; i < n; i++) {
            mp[nums[i]]++; 
        }

        priority_queue<P> maxH; 

        for(auto &it : mp) {
            int el = it.first; 
            int freq = it.second; 

            maxH.push({freq, el}); 
        }

        vector<int> res; 
        int cnt = 0; 
        while(cnt < k) {
            res.push_back(maxH.top().second); 
            maxH.pop(); 
            cnt++; 
        }

        return res; 
    }
};


// Min Heap Approach 
// TC: O(NlogK) 
// SC: O(N + K) 
class Solution {
public:
    typedef pair<int, int> P; 

    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size(); 
        unordered_map<int, int> mp;

        for(int i = 0; i < n; i++) {
            mp[nums[i]]++; 
        }

        priority_queue<P, vector<P>, greater<P>> minH; 

        for(auto &it : mp) {
            int el = it.first; 
            int freq = it.second; 

            minH.push({freq, el}); // logK
            
            if(minH.size() > k) 
                minH.pop();  // logK
        }

        vector<int> res; 

        while(!minH.empty()) {
            res.push_back(minH.top().second); 
            minH.pop(); 
        }

        return res; 
    }
};


// Unorderd Map + Frequency Vector 
// sorting the Freq vector on basis of Freqs 
// TC: O(nlogn) 
// SC: O(N) 
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size(); 
        unordered_map<int, int> mp;

        for(int i = 0; i < n; i++) {
            mp[nums[i]]++; 
        }

        vector<pair<int, int>> freqVec; 
        for(auto &it : mp) {
            freqVec.push_back({it.first, it.second}); 
        }

        auto comp = [&] (auto &a, auto &b) {
            if(a.second > b.second)
                return true; 
            
            return false; 
        }; 

        sort(freqVec.begin(), freqVec.end(), comp); 

        vector<int> res; 

        for(int i = 0; i < n; i++) {
            if(res.size() == k) 
                break; 
            res.push_back(freqVec[i].first); 
        }

        return res; 
    }
};