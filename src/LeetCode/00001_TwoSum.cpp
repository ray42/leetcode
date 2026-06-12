#include <vector>
#include <unordered_map>

class Solution1 {
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target) const {
        
        // As we go through the array, each element gives us two pieces of information:
        // The number itself, and the complement (target - number).
        // 
        // If we can find the complement in the hash map, then we have found our two numbers.
        // If the complement is not in the hash map,
        // then we can add the number and its index to the hash map because 
        // it may be a complement for a future number.

        auto numToIndex = std::unordered_map<int, int>{};
        for(auto i = 0; i < nums.size(); ++i) {
            if (const auto complement = target - nums[i];
                numToIndex.contains(complement)) {
                return {numToIndex[complement], i};
            }
            numToIndex[nums[i]] = i;
        }
        return {};
    }
};


