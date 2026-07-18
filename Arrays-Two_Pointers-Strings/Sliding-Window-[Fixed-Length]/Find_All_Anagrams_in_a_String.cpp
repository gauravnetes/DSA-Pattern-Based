#include <vector>
#include <string>
#include <unordered_map>

using namespace std; 


class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.length();  
        int k = p.length(); 

        vector<int> mp(26, 0); 
        for(char &ch : p) 
            mp[ch - 'a']++; 

        int i = 0; 
        int j = 0; 

        vector<int> res;  
        vector<int> seen(26, 0); 
        while(j < n) { 
            char ch = s[j]; 

            seen[ch - 'a']++; 

            while(seen[ch - 'a'] > mp[ch - 'a']) {
                seen[s[i] - 'a']--; 
                i++; 
            }

            if(j - i + 1 == k) {
                res.push_back(i); 
                seen[s[i] - 'a']--; 
                i++; 
            }

            j++; 
        }

        return res; 
    }
};