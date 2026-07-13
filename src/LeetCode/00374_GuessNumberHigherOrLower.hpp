#pragma once
#include <numeric>


/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

int guess(int num);

class Solution374 {
public:
  int guessNumber(int n) {
    auto lo = 1;
    auto hi = n;
    while (lo <= hi)
    {
      const auto mid = std::midpoint(lo, hi);
      if (const auto res = guess(mid); res == 0)
      {
        return mid;
      }
      else if (res  < 0)
      {
        hi = mid - 1;
      }
      else
      {
        lo = mid + 1;
      }
    }
    return -1; // This line is never reached, but added to avoid compiler warning.
  }
};


