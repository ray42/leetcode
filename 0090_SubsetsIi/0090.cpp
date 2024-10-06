

#include <vector>
#include <algorithm>

class Solution {
public:
    auto subsetsWithDup(std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        auto allSubsets = std::vector<std::vector<int>>{};

        auto currentSubset = std::vector<int>{};

        const auto numsSize = std::size(nums);
        std::ranges::sort(nums);

        auto dfs = [&numsSize, &nums, &currentSubset, &allSubsets](auto && dfs, int idx)
        {
            if(idx >= numsSize)
            {
                allSubsets.push_back(currentSubset);
                return;
            }

            // Choose nums[idx]
            currentSubset.push_back(nums[idx]);

            dfs(dfs,idx+1);

            // backtrack
            currentSubset.pop_back();

            // We need to recurse on the next non-duplicate if this is a duplicate number.
            auto j = idx + 1;
            while(j < numsSize && nums[idx] == nums[j])
            {
                ++j;
            }
            // j is either at the next index where nums[idx] == nums[j] OR, j == numsSize. So we don't need to plus 1
            dfs(dfs,j);
        };

        dfs(dfs,0);

        return allSubsets;
    }
};

auto main(int argc, char* argv[]) -> int
{



    auto iii = 42;
    return 0;

}

