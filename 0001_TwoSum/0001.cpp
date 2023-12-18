/*
EASY https://leetcode.com/problems/two-sum/

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

Constraints:

    2 <= nums.length <= 104
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    Only one valid answer exists.
 
Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?

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

auto main(int argc, char* argv[]) -> int
{
    
    return 0;
}
