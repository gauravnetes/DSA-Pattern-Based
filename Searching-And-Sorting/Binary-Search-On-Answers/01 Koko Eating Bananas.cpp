#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    bool canEatAllBananas(vector<int> &piles, int mid, int h) {
        long long actualHrs = 0; 
        for(int &x : piles) {
            actualHrs += (x / mid); 
            if(x % mid != 0) 
                actualHrs++; 
        }
        return actualHrs <= h; 
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size(); 
        int l = 1, r = *max_element(piles.begin(), piles.end()); 
        int res = 0; 

        while(l <= r) {
            int mid = l + (r - l) / 2; 
            if(canEatAllBananas(piles, mid, h)) {
                res = mid; 
                r = mid - 1; 
            } else 
                l = mid + 1; 
        }

        return res; 
    }
};