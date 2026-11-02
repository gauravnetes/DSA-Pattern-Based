#include <vector>
#include <climits>
#include <algorithm>

using namespace std; 

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size(); 

        sort(points.begin(), points.end()); 

        int i = 0, j = 1; 
        int cnt = 1; // atleast 1 arrow for the first ballon
        while(j < n) { // no overlap 
            if(points[j][0] > points[i][1]) {
                cnt++;
                i = j; 
            } else { // overlap 
                points[i][0] = max(points[i][0], points[j][0]); 
                points[i][1] = min(points[i][1], points[j][1]);
            }
            j++; 
        }

        return cnt; 
    }
};