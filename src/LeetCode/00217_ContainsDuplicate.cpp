/*
Easy https://leetcode.com/problems/contains-duplicate/

*/

#include <vector>
#include <unordered_set>
#include <type_traits>

bool containsDuplicate(std::vector<int>& nums) 
{
    // So if there is a duplicate in nums, return true. Otherwise return false.
    auto umap = std::unordered_set<std::remove_cvref_t<decltype(nums)>::value_type>{};
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
