#include<bits/stdc++.h>
using namespace std; 

// Max Heap Approach 
// TC: O(N + KlogK) -> O(N) 
// SC: O(K) -> O(1) 
class Solution {
public:
    string frequencySort(string s) {
        int n = s.length(); 

        unordered_map<int, int> mp; 
        for(char &ch : s) {
            mp[ch - 'a']++; 
        }

        priority_queue<pair<int, int>> maxH; 

        for(auto &it : mp) {
            int ch = it.first; 
            int freq = it.second; 

            maxH.push({freq, ch}); // logK
        }

        string res = ""; 
        while(!maxH.empty()) {
            int freq = maxH.top().first; 
            char ch = 'a' + maxH.top().second; 

            while(freq--) {
                res += ch; 
            }

            maxH.pop(); 
        }

        return res; 
    }
};

// Bucket Sort 
// TC: O(N + maxFreq) -> O(N) 
// SC: O(maxFreq) -> O(N) [Worst Case] 
// use for unbounded characters when K is not <= 128 and bounded 
class Solution {
public:
    string frequencySort(string s) {
        int n = s.length(); 

        int freq[128] = {0}; 
        int maxFreq = 0; 

        for(char &ch : s) {
            freq[ch]++; 
            maxFreq = max(freq[ch], maxFreq); 
        }

        vector<string> buckets(maxFreq + 1); 
        for(int c = 0; c < 128; c++) {
            if(freq[c] > 0) 
                buckets[freq[c]].push_back(static_cast<char>(c)); 
        }

        string res = ""; 
        res.reserve(n); 
        for(int f = maxFreq; f >= 0; f--) {
            for(char &ch : buckets[f]) 
                res.append(f, ch);  
        }

        return res; 
    }
};