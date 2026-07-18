// Number of Sub-arrays of Size K and Average G/reater than or Equal to Threshold


#include <vector>

using namespace std; 

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size(); 

        int i = 0, j = 0; 
        int currSum = 0; 
        int subArrCnt = 0; 

        while(j < n) {
            currSum += arr[j];
            if(j-i+1 == k) {
                if((currSum / k) >= threshold) {
                    subArrCnt++; 
                }
                currSum -= arr[i]; 
                i++; 
            }

            j++; 
        }
        return subArrCnt; 
    }
};