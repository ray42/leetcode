/*

*/


#include <vector>
#include <type_traits>

class Solution {
public:
    auto permute(std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        auto res = std::vector<std::vector<int>>{};

        permute(nums, 0, res);

        return res;
    }

private:

    auto permute(std::vector<int>& nums, int idx, std::vector<std::vector<int>>& res) -> void
    {
        // We do not swap the last one since there is only 1 permutation of 1 object.
        if(idx == nums.size() - 1)
        {
            res.push_back(nums);
        }

        for(auto idxToSwap = idx; idxToSwap < nums.size(); ++idxToSwap) // This is the branches
        {
            std::swap(nums[idx], nums[idxToSwap]);
            permute(nums, idx + 1, res); // This goes into the next level

            // backtrack
            std::swap(nums[idx], nums[idxToSwap]);
        }
    }
};







class SolutionPractice {
public:
    auto permute(std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        
        auto allPerms = std::vector<std::vector<std::remove_cvref_t<decltype(nums)>::value_type>>{};
        const auto& numsSize = std::ssize(nums);

        auto dfs = [&](auto&& dfs, int idxToSwap)
        {
            if(idxToSwap == numsSize - 1)
            {
                // We don't swap the last one, so we can just add the result and return;
                allPerms.push_back(nums);
                return;
            }

            for(auto j = idxToSwap; j < numsSize; ++j)
            {
                std::swap(nums[idxToSwap], nums[j]);
                // Continue on to the next index to swap

                dfs(dfs, idxToSwap+1);
                
                // backtrack
                std::swap(nums[j], nums[idxToSwap]);
            }
            
        };

        dfs(dfs, 0);

        return allPerms;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto v = std::vector{1,2,3};
    auto iii = Solution{}.permute(v);
    auto i = 42;
    return 0;
}

