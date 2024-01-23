
#include <vector>
#include <algorithm>

class Solution {
public:
    auto findErrorNums(std::vector<int>& nums) -> std::vector<int>
    {
        std::ranges::sort(nums);

        const auto numsSize = nums.size();

        auto repeated = 0;
        auto missing = 0;

        for(auto i = 1; i < numsSize; ++i)
        {
            if(nums[i] == nums[i-1])
            {
                repeated = nums[i];
            }
            if(nums[i] - nums[i-1] == 2)
            {
                missing = nums[i-1] + 1;
            }
        }

        // If missing = 0, then either the 1 is missing or n is missing.
        if(missing == 0)
        {
            missing = nums[0] == 1 ? numsSize : 1;
        }
        return {repeated, missing};
    }
};