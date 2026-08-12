#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std; 

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length(); 
        int req = t.length(); 
        
        if(n < req) return ""; 

        int mp[128] = {0}; 

        for(char ch : t) {
            mp[ch]++; 
        }

        int i = 0, j = 0; 
        int cnt = 0; 
        int minLen = INT_MAX; 
        int startIdx = -1; 

        while(j < n) {
            if(mp[s[j]] > 0) {
                cnt++; 
            }
            mp[s[j]]--; 

            while (cnt == req) {
                if(j-i+1 < minLen) {
                    minLen = j-i+1; 
                    startIdx = i; 
                }

                mp[s[i]]++; 
                if(mp[s[i]] > 0) 
                    cnt--; 

                i++; 
            }
            j++; 
        }

        return startIdx == -1 ? "" : s.substr(startIdx, minLen); 
    }
};