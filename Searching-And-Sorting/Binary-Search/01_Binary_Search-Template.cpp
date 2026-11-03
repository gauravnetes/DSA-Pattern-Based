#include <vector>
using namespace std;

// BS: Iterative 
// TC: O(logN)
// SC: O(1)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(); 
        int l = 0, r = n-1; 

        while(l <= r) {
            int mid = l + (r - l) / 2; 
            if(nums[mid] == target) 
                return mid; 
            else if(nums[mid] < target) 
                l = mid + 1; 
            else 
                r = mid - 1; 
        }

        return -1; 
    }
};

// BS: Recursive 
// TC: O(logN) 
// SC: O(logN) // Recursive Stack Space
// O(1) // No Auxilary Space  
class Solution {
public:
    int bS(vector<int> &nums, int l, int r, int target) {
        if(l > r)   
            return -1; 

        int mid = l + (r - l) / 2; 
        if(nums[mid] == target)
             return mid; 
        else if(nums[mid] < target) 
            return bS(nums, mid + 1, r, target); 
        else 
            return bS(nums, l, mid - 1, target);
    }

    int search(vector<int>& nums, int target) {
        int n = nums.size(); 
        int l = 0, r = n-1; 

        return bS(nums, l, r, target); 
    }
};