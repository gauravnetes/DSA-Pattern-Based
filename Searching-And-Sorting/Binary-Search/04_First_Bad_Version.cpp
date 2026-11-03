#include<bits/stdc++.h>
using namespace std; 

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
bool isBadVersion(int mid){
    return true; 
}; 

// lower_bound 
class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1, h = n; 
        while(l < h) {
            int mid = l + (h - l) / 2; 
            if(!isBadVersion(mid)) {
                l = mid + 1; 
            } else {
                h = mid; 
            }
        }

        return l; 
    }
};

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1, h = n; 
        while(h - l > 1) {
            int mid = l + (h - l) / 2; 
            if(!isBadVersion(mid)) {
                l = mid + 1; 
            } else {
                h = mid; 
            }
        }

        if(isBadVersion(l))
            return l; 
        if(isBadVersion(h))
            return h; 
        return -1; 
    }
};