#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    bool shipAllPackages(vector<int>& weights, int days, int cap) {
        int n = weights.size();
        int reqDays = 1; 

        int currWt = 0;
        for (int& wt : weights) {
            // if adding this package exceeds cap, send the ship, increment reqDays
            if(currWt + wt > cap) {
                reqDays++; 
                currWt = wt; 
            } else {
                currWt += wt; 
            }
        }
        return reqDays <= days; 
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        int totalWt = accumulate(weights.begin(), weights.end(), 0); 

        // as we're not allowed to split a package in half. The minimum cap 
        // must be = the max weighted package present on the belt 
        int l = *max_element(weights.begin(), weights.end()); 
        int r = totalWt;

        int res = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (shipAllPackages(weights, days, mid)) {
                res = mid;
                r = mid - 1; // we need least weight capacity
            } else {
                l = mid + 1; // expand the capacity
            }
        }
        return res;  
    }
};