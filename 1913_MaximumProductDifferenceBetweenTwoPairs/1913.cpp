/*
EASY: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/

The product difference between two pairs (a, b) and (c, d) is defined as (a * b) - (c * d).

    For example, the product difference between (5, 6) and (2, 7) is (5 * 6) - (2 * 7) = 16.

Given an integer array nums, choose four distinct indices w, x, y, and z such that the product difference between pairs (nums[w], nums[x]) and (nums[y], nums[z]) is maximized.

Return the maximum such product difference.

Example 1:

Input: nums = [5,6,2,7,4]
Output: 34
Explanation: We can choose indices 1 and 3 for the first pair (6, 7) and indices 2 and 4 for the second pair (2, 4).
The product difference is (6 * 7) - (2 * 4) = 34.

Example 2:

Input: nums = [4,2,5,9,7,4,8]
Output: 64
Explanation: We can choose indices 3 and 6 for the first pair (9, 8) and indices 1 and 5 for the second pair (2, 4).
The product difference is (9 * 8) - (2 * 4) = 64.

Constraints:

    4 <= nums.length <= 104
    1 <= nums[i] <= 104

Ray Notes:

So we need to get the two smallest numbers and two largest numbers. How do we do that?
Well, since we know that 4 <= nums.length <= 104, we can initialise
largest, secondLargest, secondSmallest, smallest to the first 4 numbers of nums (in sorted order).
Then, we loop through nums i = 4.. < nums.size() and if we get a number bigger than largest, we assign secondLargest = largest and set the new largest
we do the same for the smallest

*/
#include <vector>

#include <algorithm> 

class Solution 

{

public:

    int maxProductDifference(std::vector<int>& nums) 

    {

        //auto firstFour = std::vector<int>(nums.begin(), nums.begin() + 4);

        std::ranges::sort(nums.begin(), nums.begin() + 4);

        auto smallest = nums[0];

        auto secondSmallest = nums[1];

        auto secondLargest = nums[2];

        auto largest = nums[3];



        for(auto i = 4; i < nums.size(); ++i)

        {

            if(nums[i] < smallest)
            {
                secondSmallest = smallest;
                smallest = nums[i];
            }
            else if(nums[i] < secondSmallest)
            {
                secondSmallest = nums[i];
            }

            if(nums[i] > largest)
            {
                secondLargest = largest;
                largest = nums[i];
            }
            else if(nums[i] > secondLargest)
            {
                secondLargest = nums[i];
            }
        }
        return largest * secondLargest - secondSmallest * smallest;
    }
};

auto main(int argc, char* argv[])->int
{
    
}
