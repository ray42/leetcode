/*
https://leetcode.com/problems/contains-duplicate/

Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

Example 1:

Input: nums = [1,2,3,1]
Output: true

Example 2:

Input: nums = [1,2,3,4]
Output: false

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true

Constraints:

    1 <= nums.length <= 105
    -109 <= nums[i] <= 109
*/

#include <vector>
#include <unordered_set>
bool containsDuplicate(std::vector<int>& nums) 
{
    // So if there is a duplicate in nums, return true. Otherwise return false.
    auto umap = std::unordered_set<int>{};
    for(const auto& i : nums)
    {
        if(!umap.insert(i).second)
        {
            return true;
        }
    }
    return false;
}

auto main(int argc, char *argv[]) -> int
{
    
}
