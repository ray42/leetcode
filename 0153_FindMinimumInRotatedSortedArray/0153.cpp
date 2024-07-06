/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. 
For example, the array nums = [0,1,2,4,5,6,7] might become:

    [4,5,6,7,0,1,2] if it was rotated 4 times.
    [0,1,2,4,5,6,7] if it was rotated 7 times.

Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in 
the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

Example 1:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
--------------------------------------------------------
If we were to use binary search, what is the condition to search left or right?

        0 1 2 3 4 5 6
nums = [3,4,5,6,0,1,2]
        L     M     R

So we set res = M = 7 as the initial result.
But how do we know to look left or right? If nums is rotated, then there are two increasing segments:
[3,4,5,6],[0,1,2]
Every element on the left segment is greater than or equal to the right segment.


So if the M is in the left segment:
[3,4,5,6],[0,1,2] It must be the case that nums[L] <= nums[M]. We must have <= because when we have two element left, then L==M. [3,4]
 L     M       R                                                                                                                  L R
                                                                                                                                  M
In this case, we look RIGHT.

Otherwise, nums[L] > nums[M] and so we look LEFT.
[6],[0,1,2,3,4,5]
 L       M

This works for when M is on the smallest element because we only update the result if M the smaller than the current result.
In the case below, we set res = 0, and then we look right, but because 1,2,3 are not smaller than 0, we never set them to res.
[4,5,6],[0,1,2,3]
 L       M     R

Here, nums[L] <= nums[M], so we look RIGHT. But this doesn't work! since initially, our result is 3, then when we look right,
we find 4,5,6. And so at the end, we return 3. This is WRONG.
[0,1,2,3,4,5,6]
 L     M     L

 So what do we do in this case? We need to detect that this is not rotated. But how? Note that if there is a rotation, then
 (from above), we have: "Every element on the left segment is greater than or equal to the right segment.", but in a non-rotated array, this is not true.
 In a non-rotated array, nums[L] < nums[R]. In this case, we can return nums[L] immediately.
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    auto findMin(const std::vector<int>& nums) -> int
    {
        auto L = 0;
        auto R = nums.size()-1;
        auto res = nums[0];
        while(L <= R)
        {
            // Check if not rotated
            if(nums[L] < nums[R])
            {
                res = std::min(res,nums[L]);
                break;
            }

            const auto M = (L + R)/2;
            
            res = std::min(res,nums[M]);
            if(nums[L] <= nums[M])
            {
                L = M+1;
            }
            else
            {
                R = M-1;
            }
        }

        return res;
    }
};



auto main(int argc, char* argv[]) -> int
{
    return 0;
}

