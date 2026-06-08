/*
https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/
*/
#include <vector>
#include <algorithm>
#include <numeric>

class Solution 
{
public:
using ll = long long;

    auto largestPerimeter(std::vector<int>& nums) -> ll
    {
        // Sort
        
        // Sum all 
        // Go right to left. 
        //     for each i, 
        //         if sum - k_i > k_i, return sum.
        //         otherwise, set sum -= k_i and go again.
        std::ranges::sort(nums);
        auto sum = std::accumulate(nums.begin(), nums.end(),ll{0});

        for(auto i = nums.size() - 1; i >= 2; --i)
        {
            if(sum - nums[i] > nums[i])
            {
                return sum;
            }

            sum -= nums[i];
        }

        return -1;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

