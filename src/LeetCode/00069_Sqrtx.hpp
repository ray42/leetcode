#pragma once
#include <numeric>

class Solution69 {
public:
  int mySqrt(int x) {
    int left = 1;
    int right = x;

    while (left <= right) {
      int mid = std::midpoint(left, right);

      // Force multiplication to occur using long long,
      // preventing overflow when mid is large.
      long long square = 1LL * mid * mid;

      if (square == x) {
        return mid;
      }

      if (square < x) {
        // mid is valid, but there may be a larger valid answer.
        //
        // Example: x = 5 and mid = 2:
        // 2² = 4 <= 5, so continue searching to the right.
        left = mid + 1;
      }
      else {
        // mid is invalid because its square is too large.
        //
        // Example: x = 5 and mid = 3:
        // 3² = 9 > 5, so continue searching to the left.
        right = mid - 1;
      }
    }

    // right is the largest integer whose square is <= x.
    // left is the smallest integer whose square is > x.
    //
    // Example: x = 5
    //
    // possible values: [1, 2 | 3, 4, 5]
    //                       R   L
    //
    // Since integer square root rounds down, return right.
    return right;
  }
};
