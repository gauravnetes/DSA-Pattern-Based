#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:     
    bool canMakeAllBouquets(vector<int>& bloomDay, int m, int k, int days) {
        int count = 0; 
        int bouquetCnt = 0; 

        for(int &b : bloomDay) {
            if(b > days) {
                count = 0; 
            } else {
                count++; 
                if(count == k) {
                    bouquetCnt++; 
                    count = 0; 
                }
            }
        }

        return bouquetCnt >= m; 
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size(); 

        if(n < (1LL * m*k))
            return -1; 

        int l = *min_element(bloomDay.begin(), bloomDay.end()); 
        int r = *max_element(bloomDay.begin(), bloomDay.end()); 
        int res = 0; 
        
        while(l <= r) {
            int mid = l + (r - l) / 2; 

            if(canMakeAllBouquets(bloomDay, m, k, mid)) {
                res = mid; 
                r = mid - 1; 
            } else {
                l = mid + 1; 
            }
        }
        return res; 
    }
};