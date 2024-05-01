/*
EASY https://leetcode.com/problems/two-sum/

Ray Notes:
So in this array: [3,2,4], we need to find the indices of two numbers that adds up to 6.

Naive Method:
Start at the left of the array and add that value to each of the values on the right.
e.g. 
for(auto i = 0; i < nums.size(); ++i)
{
  for(auto j = i+1 ; j < nums.size(); ++i)
  {
    if(nums[i] + nums[j] == target)
    {
        return {i,j};
    }
  }
}

This is O(n^2) time and O(1) space.

One pass method:

We loop through the array nums, for each number in nums, we know three things:
the current number nums[i], the target, and we can calculate what we need to add to nums[i] to make the target.
So what we can do is, for each nums[i], we calculate the composite: target = nums[i] and check in a store to see if we have come across it before.
    if we have not come across it, then store nums[i] and i in the store since it could be a compliment for a value nums[j] where i < j < nums.size()
    if we do find the composite in the store, then we can just return i and the index stored in the store.

    It's apparent now that the store has to be a map where the keys are values from nums and the values is the index of the value in nums:
    map: nums[x] -> x
*/

#include <vector>
#include <unordered_map>
#include <type_traits>
#include <ranges>

class Solution {
public:
    auto twoSum(const std::vector<int>& nums, int target) -> std::vector<int>
    {
        // Some fancy type deduction!
        auto valuesToIndices = std::unordered_map<std::remove_cvref_t<decltype(nums)>::value_type,int>{};
        for(auto i = 0; i < nums.size(); ++i)
        {
            const auto& num = nums[i];
            const auto& compliment = target - num;
            if(auto it = valuesToIndices.find(compliment); it != valuesToIndices.end())
            {
                // Compliment found!
                return {i, it->second};
            }
            
            // Compliment not found :(
            valuesToIndices.try_emplace(num, i);
        }
        return {}; // No solution
    }
};


class Solution2 {
public:
    // You may assume that each input would have exactly one solution, and you may not use the same element twice.
    // The "you may not use the same element twice" is important because, say, if the target is 10, and we have 5 and 5 in the list
    // but at different indices, say 3 and 7, we have to return [3,7] (or [])
    auto twoSum(const std::vector<int>& nums, int target) -> std::vector<int>
    {
        // Store a map of values to indices, where the values are the complements of some number in nums minus the target.
        // The value is the index of the number because we are required to return the index.
        auto complements = std::unordered_map<std::remove_cvref_t<decltype(nums)>::value_type,int>{};

        // The logic: For each value in nums, we try to find it's complement in complements.
        // If the complement does not exist in complements, then it means that this value 
        // could be a complement for some other value so we put it in the complements map.
        //for(const auto& [index, value] : std::views::enumerate(nums)) // This is in C++23 only.
        for(auto index = 0; index < nums.size(); ++index)
        {
            const auto& value = nums[index];

            const auto complement = target - value;
            if(const auto iter = complements.find(complement); iter != complements.end())
            {
                return {index, iter->second};
            }
            complements.try_emplace(value,index);
        }

        return {};
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution2{}.twoSum({2,7,11,15},9);
    return 0;
}
