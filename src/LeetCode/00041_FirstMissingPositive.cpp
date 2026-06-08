#include <vector>

/*
This is a pretty good solution: https://leetcode.com/problems/first-missing-positive/solutions/4925619/hard-easy-positioning-elements-at-correct-index/

Question here: 
Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.
You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.

Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.

Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.

Constraints:

    1 <= nums.length <= 105
    -231 <= nums[i] <= 231 - 1

RAY COMMENTS:
The trick here is to realise that the answer MUST be in the range [1,n], where n is the size of the array.
Why? Because the SMALLEST missing positive integer must be in that range if we have something else in there.
E.g. this has nothing missing: [1,2,3,4,5], but as soon as there is a missing integer, e.g.
[1,12,3,4,5], then it must be one of the 1 to 5 digits. That is, it must be from 1 to n. In this case, it is 2.

What we have to do is figure out how to use this fact to come up with a solution that
that runs in O(n) time and uses O(1) auxiliary space.

So, O(n) means we visit all elements a constant amount of time, and 
O(1) basically indicates that I cannot use a hash map or something because that will be O(n)
In fact, O(1) space usually means that I have to use the input array itself.

So how do I perform this? What we can do is to loop through the nums array, and for each element:
If the element is valid (in the range [1,n]), then
    Keep putting the value of the element into the index (minus 1) until the value becomes not valid.

    E.g.
            0   1  2  3
    nums = [3,  4,-1, 1] // We put 3 in i = 2 (so a swap with nums[val-1])
           [-1, 4, 3, 1] // -1 is not valid, so we move onto the next element, swap 4 and what's in nums[4-1]

           [-1, 1, 3, 4] // 1 is valid, so swap 1 with nums[0]
           [1, -1, 3, 4] // -1 is not valid. Move onto the next one.

           [1, -1, 3, 4] // 3 is in it's place (index 2), move onto the next one

           [1, -1, 3, 4] // 4 is in it's place (index 3), move onto the next one - there is no next one, we are done!

Now we loop through the array once more to see which nums[i] != i+1, e.g. nums[0] = 1. The first one we come across is
the smallest missing positive.
*/

class Solution {
public:
    auto firstMissingPositive(std::vector<int>& nums) -> int
    {
        const auto n = nums.size();
        for(auto i = 0; i < n; ++i)
        {
            auto val = nums[i];
            // Do we need to swap?
            // val != i + 1 says that if the current value is not in the correct place, then we move it. 
            // nums[val-1] != val says that if the place we want to move it to already has the correct element, then we skip.
            //     The last condition is very important for cases like [1,1] and we have an infinite loop.
            //     Since if we try to move the last 1 to the correct place, we will move it with the 1 at index 0.
            //         then this cycle will repeat over and over again.
            while(val >= 1 && val <= n && val != i + 1 && nums[val-1] != val)
            {
                // Where should we put this value?
                std::swap(nums[i], nums[val-1]); // Remember that val is in [1,n], so we need to -1.
                val = nums[i]; // Remember to update the value!
            }
        }

        // Now we loop through and find the missing value
        for(auto i = 0; i < n; ++i)
        {
            if(nums[i] != i + 1) return i+1;
        }

        // If ALL the values in the array are there, then the next highest should be taken as the smallest missing number.
        // E.g. if the final array is [1,2,3,4,5], then we will return 6 - this is the most logical choice.
        return n+1;
    }
};


auto main(int argc) -> int
{
    return 0;
}
