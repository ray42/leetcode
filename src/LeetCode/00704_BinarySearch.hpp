#pragma once
#include <iterator>
#include <vector>

class Solution704 {
public:
  int search(const std::vector<int>& nums, int target) const {
    int lo = 0;
    int hi = static_cast<int>(nums.size()) - 1;

    // Invariant:
    // If target exists, its index is inside the inclusive range [lo, hi].
    //
    // Example with nums = {-1, 0, 3, 5, 9, 12}:
    // Initially [lo, hi] = [0, 5], so every index is a candidate.
    while (lo <= hi) {
      // Prefer this over (lo + hi) / 2 to avoid potential overflow.
      int mid = lo + (hi - lo) / 2;

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[mid] < target) {
        // Example: nums[mid] = 3 and target = 9.
        // Since the array is sorted, indices <= mid are too small.
        // Exclude mid by moving lo to mid + 1.
        lo = mid + 1;
      }
      else {
        // Example: nums[mid] = 9 and target = 3.
        // Since the array is sorted, indices >= mid are too large.
        // Exclude mid by moving hi to mid - 1.
        hi = mid - 1;
      }
    }

    // lo > hi means the inclusive candidate range is empty.
    return -1;
  }
};


// GPT came up with this which is interesting:
class Solution704GptSolution {
public:
  int search(const std::vector<int>& nums, int target) const {
    // Search range is [lo, hi):
    // Example: for 5 elements, candidates initially are [0, 5),
    // meaning indices 0, 1, 2, 3, and 4.
    int lo = 0;
    int hi = static_cast<int>(nums.size());

    // Invariant: if target exists, its index is inside [lo, hi).
    while (lo < hi) {
      // Avoids the potential overflow of (lo + hi) / 2.
      int mid = lo + (hi - lo) / 2;

      if (nums[mid] < target) {
        // Example: nums[mid] = 4 and target = 9.
        // mid and everything left of it are too small.
        lo = mid + 1;
      }
      else {
        // Example: nums[mid] = 9 and target = 9:
        // keep mid because it may be the answer.
        //
        // If nums[mid] = 12 and target = 9:
        // mid and everything to its right cannot be the answer.
        hi = mid;
      }
    }

    // The range is empty. lo is the only possible matching position.
    if (lo < static_cast<int>(nums.size()) && nums[lo] == target) {
      return lo;
    }

    return -1;
  }
};


/*
auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution704{}.search({5}, 5);
    return 0;
}
*/
