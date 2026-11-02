#include <vector>
#include <climits>
#include <algorithm>

using namespace std; 

// Standard O(N) approach
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size(); 
        if(n == 0) return {newInterval};

        int i = 0; 
        vector<vector<int>> res; 

        while (i < n) {
            if(intervals[i][1] < newInterval[0]) {
                res.push_back(intervals[i]); 
            } else if(intervals[i][0] > newInterval[1]) {
                break; 
            } else if(newInterval[0] <= intervals[i][1]) {
                newInterval[0] = min(newInterval[0], intervals[i][0]); 
                newInterval[1] = max(newInterval[1], intervals[i][1]); 
            } 
            i++; 
        }

        res.push_back(newInterval); 

        while(i < n) {
            res.push_back(intervals[i]); 
            i++; 
        }

        return res; 
    }
};



// Using Merge Intervals Approach - O(NlogN) | Overall O(N) due to shifting
class Solution {
public:
    vector<vector<int>> mergeIntervals(vector<vector<int>> &intervals) {
        int n = intervals.size(); 
        if(n == 1) return intervals;

        sort(intervals.begin(), intervals.end()); 

        vector<vector<int>> res; 
        res.push_back(intervals[0]); 

        for(int i = 1; i < n; i++) {
            if(intervals[i][0] <= res.back()[1]) {
                res.back()[0] = min(res.back()[0], intervals[i][0]); 
                res.back()[1] = max(res.back()[1], intervals[i][1]); 
            } else {
                res.push_back(intervals[i]); 
            }
        }

        return res; 
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval); 
        return mergeIntervals(intervals); 
    }
};


// Binary Search Approach ~ O(logN)

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size(); 

        int left = 0, right = n-1; 
        int startIdx = n; 

        while(left <= right) {
            int mid = left + (right - left) / 2; 
            if(intervals[mid][1] >= newInterval[0]) {
                startIdx = mid; 
                right = mid - 1; 
            } else {
                left = mid + 1; 
            }
        }

        left = 0, right = n-1; 
        int endIdx = n; 

        while(left <= right) {
            int mid = left + (right - left) / 2; 
            if(intervals[mid][0] > newInterval[1]) {
                endIdx = mid; 
                right = mid - 1; 
            } else {
                left = mid + 1; 
            }
        }

        if(startIdx < endIdx) {
            newInterval[0] = min(intervals[startIdx][0], newInterval[0]); 
            newInterval[1] = max(intervals[endIdx-1][1], newInterval[1]); 
        }

        vector<vector<int>> res; 
        for(int i = 0; i < startIdx; i++) {
            res.push_back(intervals[i]); 
        }

        res.push_back(newInterval); 

        for(int i = endIdx; i < n; i++) {
            res.push_back(intervals[i]); 
        }

        return res; 
    }
};