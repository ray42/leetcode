#pragma once
#include <vector>
#include <iterator>
#include <numeric>

class Solution74 {
public:
  bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) const {
    auto L = 0LL;
    auto R = static_cast<long long>(std::ssize(matrix)) * std::ssize(matrix[0]) - 1;
    
    const auto colSize = static_cast<long long>(std::ssize(matrix[0]));

    while (L <= R)
    {
      auto M = std::midpoint(L, R);
      auto row = M / colSize;
      auto col = M % colSize;
      if (target < matrix[row][col])
      {
        R = M - 1;
      }
      else if (target > matrix[row][col])
      {
        L = M + 1;
      }
      else
      {
        return true;
      }
    }

    return false;
  }
};
