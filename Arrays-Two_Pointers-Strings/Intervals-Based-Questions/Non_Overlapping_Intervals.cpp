#include <vector>
#include <climits>
#include <algorithm>

using namespace std; 

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size(); 
        sort(intervals.begin(), intervals.end());

        int cnt = 0; 
        int i = 0, j = i+1; 

        while(j < n) {
            if(intervals[i][1] <= intervals[j][0]) {
                i = j; 
                j++; 
            } else {
                if(intervals[i][1] >= intervals[j][1]) {
                    i = j; 
                    j++; 
                    cnt++; 
                } else if(intervals[j][1] > intervals[i][1]) {
                    j++;
                    cnt++;  
                }
            }
        }
        return cnt; 
    }
};