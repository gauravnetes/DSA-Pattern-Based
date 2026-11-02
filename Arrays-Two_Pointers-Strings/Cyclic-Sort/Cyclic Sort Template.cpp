#include <vector>
using namespace std;

void cyclicSort(vector<int> &nums) {
    int i = 0;
    int n = nums.size();

    while (i < n) {
        int correctIdx = nums[i] - 1;

        // 1. Check bounds (if the problem allows out-of-range numbers)
        // 2. The core duplicate check to prevent infinite loops
        if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[correctIdx]) {
            swap(nums[i], nums[correctIdx]);
        } else {
            i++;
        }
    }
}