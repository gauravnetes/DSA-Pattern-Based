#include <bits/stdc++.h>
using namespace std; 

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> events;
        for (const auto& building : buildings) {
            int l = building[0], r = building[1], h = building[2];
            events.push_back({l, -h, 1}); // 1 -> building start
            events.push_back({r, h, 0}); // 0 -> buildiing end
        }
        sort(events.begin(), events.end()); 

        multiset<int, greater<int>> activeH;
        vector<vector<int>> skyLine;
        int prevMax = 0;

        for (const auto& event : events) {
            int x = event[0], h = abs(event[1]);
            bool isStart = event[2] == 1;
            if (isStart)
                activeH.insert(h);
            else
                activeH.erase(activeH.find(h));

            int currMax = activeH.empty() ? 0 : *activeH.begin();
            if (currMax != prevMax) {
                skyLine.push_back({x, currMax});
                prevMax = currMax;
            }
        }
        return skyLine; 
    }
};