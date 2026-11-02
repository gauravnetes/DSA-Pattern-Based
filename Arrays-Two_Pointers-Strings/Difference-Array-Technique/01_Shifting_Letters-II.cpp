#include <vector>
#include <string>
#include <unordered_map>

using namespace std; 

class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.length(); 
        vector<int> diff(n, 0);

        for(auto &shift : shifts) {
            int L = shift[0]; 
            int R = shift[1]; 
            
            int forward = (shift[2] == 1); 
            int x = forward ? 1 : -1; 

            diff[L] += x; 
            if(R+1 < n) {
                diff[R+1] -= x; 
            }
        }

        // cum-sum 
        for(int i = 1; i < n; i++) {
            diff[i] = diff[i-1] + diff[i]; 
        }

        for(int i = 0; i < n; i++) {
            int shifts = diff[i] % 26; 
            if(shifts < 0) 
                shifts += 26; 

            s[i] = (((s[i] - 'a') + shifts) % 26) + 'a'; 
        }

        return s; 
    }
};