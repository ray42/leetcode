
#include <vector>

class Solution {
public:
    auto numSubarraysWithSum(std::vector<int>& nums, int goal) -> int
    {
        // We use a sliding window. 
        // We begin with the two pointers at that start, and shift the right
        // pointer until the partial sum is greater than goal (whilst) counting
        // the number of times they are equal goal
        // Then we shift the left pointer to the right by one
        // then we keep shifting the right pointer again.
        // 
        // Once the right pointer reaches the end of the list, we shift the
        // left pointer until the partial sum is less than goal.
        // We can do the last bit because there are only 0 and 1s, that is
        // there are no minuses which makes sure we have to make the left
        // and right pointer reach the end. OH NO, the goal could be 0...
        // Maybe it's best to move the left and right pointer to the right
        // until they both reach the end.

        auto count = int{};

        auto left = 0;
        auto right = 0;

        auto partialTotal = nums[left] + nums[right];
        const auto numsSize = nums.size();
        
        while(left < numsSize && right < numsSize)
        {
            if(partialTotal == goal && right < numsSize)
            {
                ++count;
                ++right;
                partialTotal += nums[right];
            }
            else if(partialTotal < goal && right < numsSize)
            {
                ++right;
                partialTotal += nums[right];
            }
            else
            {
                partialTotal -= nums[left];
                --left;
                if(partialTotal == goal) ++count;
            }
            //while(nums[left])

        }

    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
