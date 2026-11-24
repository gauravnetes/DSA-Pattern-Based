#include<bits/stdc++.h>
using namespace std; 

// Max Heap Approach 
// TC: 
class Solution {
public:
    typedef pair<int, pair<int, int>> P; 

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n = points.size(); 

        priority_queue<P> maxH; 

        for(auto &point : points) {
            int x1 = point[0]; 
            int y1 = point[1]; 

            int dist = x1 * x1 + y1 * y1; 
            maxH.push({dist, {x1, y1}}); // { dist, {x, y} }

            if(maxH.size() > k)     
                maxH.pop(); 
        }

        vector<vector<int>> res; 

        while(!maxH.empty()) {
            int x = maxH.top().second.first; 
            int y = maxH.top().second.second; 

            res.push_back({x, y}); 
            maxH.pop(); 
        }

        return res; 
    }
};