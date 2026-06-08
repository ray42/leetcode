#include <vector>
#include <type_traits>
#include <cmath>

class Solution {
public:

    // We need to return the squared values in non-decreasing order.
    // We can square all number and then sort it, leading to 
    // Time: O(nlogn), space: O(1) due to in-place sorting. However, since we know that
    // nums is in non-decreasing order, we can do better than nlogn.
    // 
    // Since we know that the magnitude of a square number is related to the absolute value of the number,
    // We can start at both ends of the array and insert the square of the bigger number at the end of the resultant array.
    // So we are trading space complexity for time complexity, since now we have
    // Time: O(n) space: O(n)
    auto sortedSquares(const std::vector<int>& nums) -> std::vector<int>
    {
        const auto& numsSize = nums.size();
        auto ans = std::remove_cvref_t<decltype(nums)>(numsSize);
        
        auto left = 0;
        auto right = static_cast<int>(numsSize - 1);
        auto ansIndex = right;

        // The = is important, since the two pointers could be on the same element but that element has yet to be processed.
        while(left <= right)
        {
            const auto& leftVal = nums[left];
            const auto& rightVal = nums[right];
            if(std::abs(leftVal) > std::abs(rightVal))
            {
                ans[ansIndex] = leftVal*leftVal;
                ++left;
            }
            else
            {
                ans[ansIndex] = rightVal*rightVal;
                --right;
            }
            --ansIndex;
        }

        return ans;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto sss = Solution{}.sortedSquares({-4,-1,0,3,10});
    return 0;
}


