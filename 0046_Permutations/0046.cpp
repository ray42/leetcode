/*

*/


#include <vector>

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

auto main(int argc, char* argv[]) -> int
{
    auto v = std::vector{1,2,3};
    auto iii = Solution{}.permute(v);
    auto i = 42;
    return 0;
}

