#include <vector> 
#include <map> 

using namespace std; 

class Solution {
  public:
    int minMeetingRooms(vector<int> &start, vector<int> &end) {
        // code here
        int n = start.size(); 
        
        map<int, int> mp;
        for(int i = 0; i < n; i++) {
            mp[start[i]]++; 
            mp[end[i]]--; 
        }
        
        int overlaps = 0; 
        int maxOverlap = 0; 
        for(auto &it : mp) {
            overlaps += it.second; 
            maxOverlap = max(overlaps, maxOverlap); 
        }
        
        return maxOverlap; 
    }
};
