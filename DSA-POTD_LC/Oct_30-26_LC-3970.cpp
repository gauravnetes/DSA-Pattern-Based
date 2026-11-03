#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    typedef tuple<int, int, int> T; 

    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        unordered_map<int, vector<vector<int>>> adj; 

        for(auto &edge : edges) {
            int u = edge[0]; 
            int v = edge[1]; 
            int wt = edge[2]; 

            adj[u].push_back({v, wt}); 
        }

        vector<vector<int>> res(n, vector<int>(k+1, INT_MAX));
        priority_queue<T, vector<T>, greater<T>> pq; // min-heap 

        res[0][1] = 0;  
        pq.push({0, 0, 1}); 

        while(!pq.empty()) {
            auto [d, node, count] = pq.top(); 
            pq.pop(); 

            if(d > res[node][count]) 
                continue; 

            if(node == n-1) 
                return d; 
            
            for(auto &vec : adj[node]) {
                int adjNode = vec[0]; 
                int wt = vec[1]; 
                int newCnt = (labels[adjNode] == labels[node]) ? count+1 : 1; 
                if(newCnt > k) 
                    continue; 

                int newDist = d + wt; 
                if(newDist < res[adjNode][newCnt]) {
                    res[adjNode][newCnt] = newDist; 
                    pq.push({newDist, adjNode, newCnt}); 
                }
            }
        }

        return -1; 
    }
};