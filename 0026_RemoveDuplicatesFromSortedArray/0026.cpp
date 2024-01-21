/*
https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
*/

#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        // We shall use two pointers. One will point to the 
        // next position to put the numbers and another will 
        // look ahead for the next unique number.
        auto numsSize = nums.size();
        auto currentPos = 0;
        for(auto nextUniqueNumPos = 1;
            nextUniqueNumPos < numsSize; ++nextUniqueNumPos)
        {
            // If the next unique number has been found, then
            // update the currentPos and put the next unique number
            // in currentPos.
            if(auto nextNumber = nums[nextUniqueNumPos];
               nums[currentPos] != nextNumber)
            {
                // Remember that pre-increment returns the incremented
                // value
                nums[++currentPos] = nextNumber;
            }
        }
        return ++currentPos;
    }
};

auto main(int argc, char* argvp[]) -> int
{
    return 0;
}

