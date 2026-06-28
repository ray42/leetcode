#pragma once
#include <vector>


class Solution27 {
public:
  int removeElement(std::vector<int>& nums, int val) const {
    auto k = 0;
      for (const auto& num : nums) {
        if (num != val) {
          nums[k++] = num;
        }
      }
      return k;
  }
};