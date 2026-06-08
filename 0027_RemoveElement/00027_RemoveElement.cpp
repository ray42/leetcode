/*
https://leetcode.com/problems/remove-element/description/
*/

#include <vector>

class Solution {
public:
    auto removeElement(std::vector<int>& nums, int val) -> int
    {
        auto numsSize = nums.size();

        // We employ the two pointer technique.
        // One of a current position an another which looks ahead.
        auto currentPos = 0;
        for(auto nextNumberPos = 0; nextNumberPos < numsSize; ++nextNumberPos)
        {
            if(const auto& n = nums[nextNumberPos]; n != val)
            {
                // post increment returns the value before incrementing.
                nums[currentPos++] = n;
            }
        }
        return currentPos;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}