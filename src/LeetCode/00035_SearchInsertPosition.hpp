#pragma once
#include <numeric>

class Solution35 {
public:
  int searchInsert(const std::vector<int>& nums, int target) const {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right) {
      int mid = std::midpoint(left, right);

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[mid] < target) {
        // nums[mid] belongs on the "less than target" side.
        //
        // Example: nums = [1, 3, 5, 6], target = 2.
        // If nums[mid] is 1, then 2 must be inserted to its right.
        left = mid + 1;
      }
      else {
        // nums[mid] belongs on the "greater than target" side.
        //
        // If nums[mid] is 3, the insertion position may be index 1
        // or somewhere further left.
        right = mid - 1;
      }
    }

    // right is the last index whose value is less than target.
    // left is the first index whose value is greater than target.
    //
    // Example: [1 | 3, 5, 6], target = 2
    //             R  L
    //
    // Insert at left to preserve sorted order.
    return left;
  }
};
