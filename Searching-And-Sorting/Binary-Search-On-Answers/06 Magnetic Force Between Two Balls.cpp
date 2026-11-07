#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    bool canPlaceAllBalls(vector<int> &pos, int force, int m) {
        int prev = pos[0]; 
        int cntBalls = 1; 

        for(int i = 1; i < pos.size(); i++) {
            if(pos[i] - prev >= force) {
                cntBalls++; 
                prev = pos[i]; 
            }
            
            if(cntBalls == m) 
                break; 
        }

        return cntBalls == m; 
    }

    int maxDistance(vector<int>& pos, int m) {
        int n = pos.size(); 
        sort(pos.begin(), pos.end()); 

        int l = 1; 
        int r = pos[n-1] - pos[0]; 
        int minF = 1; 

        while(l <= r) {
            int mid = l + (r - l) / 2; 
            if(canPlaceAllBalls(pos, mid, m)) {
                minF = mid; 
                l = mid + 1; 
            } else {
                r = mid - 1; 
            }
        }

        return minF; 
    }
};