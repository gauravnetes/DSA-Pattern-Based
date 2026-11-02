#include <bits/stdc++.h>
using namespace std; 


// OPTIMAL: O(N)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length(); 

        unordered_set<int> st;
        int maxLen = 0; 
        int i = 0, j = 0; 

        while(j < n) {
            while(st.find(s[j] - 'a') != st.end()) {
                st.erase(s[i] - 'a'); 
                i++; 
            }
            maxLen = max(j-i+1, maxLen); 
            st.insert(s[j] - 'a'); 
            j++; 
        }

        return maxLen; 
    }
};


// BRUTE FORCE - TLE: O(N*N)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        if (n == 1)
            return 1;

        unordered_set<char> st;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            int len = 0;
            for (int j = i; j < n; j++) {
                if (st.find(s[j]) != st.end()) {
                    st.clear();
                    st.insert(s[j]);
                    len = 0;
                } else {
                    len++;
                    st.insert(s[j]);
                }
                maxLen = max(len, maxLen);
            }
            st.clear(); 
        }

        return maxLen;
    }
};