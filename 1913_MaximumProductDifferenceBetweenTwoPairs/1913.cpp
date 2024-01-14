/*
EASY: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/

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
            else if(nums[i] < secondSmallest) // Need this for inputs such as [5,6,2,7,4]
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
