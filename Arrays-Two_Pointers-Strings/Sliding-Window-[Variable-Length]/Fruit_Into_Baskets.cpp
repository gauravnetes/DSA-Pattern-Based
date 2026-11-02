#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std; 

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size(); 

        int i = 0, j = 0, res = 0; 
        vector<int> mp(n, 0); 
        int distinctCnt = 0; 

        while(j < n) {
            if(mp[fruits[j]] == 0) 
                distinctCnt++; 

            mp[fruits[j]]++; 

            if(distinctCnt > 2) {
                mp[fruits[i]]--; 
                if(mp[fruits[i]] == 0) {
                    distinctCnt--; 
                }
                i++; 
            }
            res = max(res, j-i+1); 
            j++; 
        }

        return res; 
    }
};