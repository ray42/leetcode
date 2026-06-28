#include <vector>
#include <unordered_map>


class Solution169_MooreVotingAlgorithm {
public:
  int majorityElement(std::vector<int>& nums) const {
    int count = 0;
    int candidate = 0;

    // First pass: find a possible majority candidate
    for (int num : nums) {
      if (count == 0) {
        candidate = num;
      }

      if (num == candidate) {
        count++;
      }
      else {
        count--;
      }
    }

    // Second pass: verify the candidate
    int frequency = 0;

    for (int num : nums) {
      if (num == candidate) {
        frequency++;
      }
    }

    if (frequency > nums.size() / 2) {
      return candidate;
    }

    return -1; // No majority element exists
  }
};


class Solution169_hashmap
{
public:
  auto majorityElement(const std::vector<int>& nums) const -> int
  {
    const auto majorityFrequency = nums.size() / 2;
    auto numsFrequency = std::unordered_map<int, int>{};
    for (const auto& n : nums)
    {
      if (++numsFrequency[n] > majorityFrequency)
      {
        return n;
      }
    }
    return 0;
  }
};
