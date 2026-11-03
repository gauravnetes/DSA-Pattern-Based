

#include <vector>
#include <string>
#include <unordered_map>

using namespace std; 

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.length(); 

        vector<int> res; 
        int wordCnt = words.size(); 
        int k = words[0].size() * words.size(); 
        int wordLen = words[0].size();

        if(n < k) return res; 

        unordered_map<string, int> mp; 

        for(string &word : words) {
            mp[word]++; 
        }

        for(int i = 0; i < wordLen; i++) {
            int left = i; 
            unordered_map<string, int> seen; 
            int count = 0; // how many valid words are currently there in curr window 

            // sliding j by chunks of wordLen 
            for(int j = i; j < n - wordLen + 1; j += wordLen) {
                string word = s.substr(j, wordLen); 

                // word is part of our target permutation 
                if(mp.count(word)) {
                    seen[word]++; 
                    count++; 

                    // found duplicate, shrink the window from the left until the duplicate is removed
                    while(seen[word] > mp[word]) {
                        string leftWord = s.substr(left, wordLen); 
                        seen[leftWord]--; 
                        count--; 
                        left += wordLen; 
                    }

                    if(count == wordCnt) {
                        res.push_back(left); 
                    }
                    
                // word is completely invalid and not in the words array 
                } else {
                    seen.clear(); 
                    count = 0; 
                    left = j + wordLen; 
                }
            }
        }

        return res; 
    }
};