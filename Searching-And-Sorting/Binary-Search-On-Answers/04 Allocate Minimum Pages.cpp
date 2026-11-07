#include<bits/stdc++.h>
using namespace std; 

class Solution {
  public:
    int solve(vector<int> &arr, long long pages) {
        int students = 1; 
        long long currStudentPages = 0; 
        
        for(int i = 0; i < arr.size(); i++) {
            if(currStudentPages + arr[i] <= pages) {
                currStudentPages += arr[i]; 
            } else {
                students++; 
                currStudentPages = arr[i]; 
            }
        }
        return students; 
    }
    
    int findPages(vector<int> &arr, int m) {
        // code here
        int n = arr.size(); 
        if(n < m) 
            return -1; 
            
        long long l = *max_element(arr.begin(), arr.end()); 
        long long r = accumulate(arr.begin(), arr.end(), 0LL); 
        long long ans = 0; 
        
        while(l <= r) {
            long long mid = l + (r - l) / 2; 
            
            int studentsCnt = solve(arr, mid); 
            
            if(studentsCnt > m) {
                l = mid + 1; 
            } else {
                ans = mid; 
                r = mid - 1; 
            }
        }
        
        return (int) ans; 
    }
};