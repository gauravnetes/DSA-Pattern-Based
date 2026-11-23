#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int maxVal = *max_element(nums.begin(), nums.end()) + k;

        map<int, int> diff;
        unordered_map<int, int> freq;

        // O(nlogn)
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++;

            int l = max(nums[i] - k, 0);
            int r = min(nums[i] + k, maxVal);

            diff[l]++;
            diff[r + 1]--;

            diff[nums[i]] += 0;
        }

        int res = 1;
        int cumSum = 0;

        // O(n)
        for (auto it = diff.begin(); it != diff.end(); it++) {
            int target = it->first;
            it->second += cumSum;

            int targetFreq = freq[target];
            int needConversion = it->second - targetFreq;

            int maxPossibleFreq = min(needConversion, numOperations);
            res = max(res, maxPossibleFreq + targetFreq);

            cumSum = it->second;
        }

        return res;
    }
};