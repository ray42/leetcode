/*
EASY https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array

Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.

Example 1:

Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6

Example 2:

Input: arr = [1,1]
Output: 1

Constraints:
    1 <= arr.length <= 104
    0 <= arr[i] <= 105
*/

#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>

class Solution {
public:
    auto findSpecialInteger(const std::vector<int>& arr) -> int
    {
        // Find the ceiling of 25% - we need to +1 to get one higher than 25% if
        // 25% is an exact integer in case where are more than one values which are 
        // 25%.
        const auto r25percent = static_cast<int>(std::floor(arr.size()*0.25 + 1));
        auto frequency = std::unordered_map<int,int>{};
        auto ret = 0;
        for(const auto& i : arr)
        {
            ++frequency[i];
            if(frequency[i] >= r25percent)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }
};

auto main(int argc, char * argv[]) -> int
{
    auto ii = Solution{}.findSpecialInteger({1,2,3,3});
    std::cout << ii << std::endl;
    return 0;
}
