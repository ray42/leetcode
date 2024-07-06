/*
There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) 
such that the resulting array is 
[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). 
For example, 
[0,1,2,4,5,6,7] might be rotated at pivot index 3 and become 
[4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, 
return the INDEX of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:

Input: nums = [1], target = 0
Output: -1
-----------------------------------------------------------

if nums[M] == target, return M.

If sorted - must do this one before "M on left segment", since the condition for "M on left segment" also satisfies this one.
[0,1,2,3,4,5,6]
 L     M     R
if(nums[L] < nums[R]) && target < nums[M], look left
                      && target > nums[M], look right


M on left segment - note: a SEGMENT is an increasing segment, e.g. these are the two segments: [3,4,5,6],[0,1,2] 
[3,4,5,6,0,1,2], target = 0
 L     M     R
if nums[L] <= nums[M] (means M is on the left segment). If the target is bounded by the left segment, then search there
                                                        nums[L] <= target && target < nums[M] -> look left
                                                        otherwise look right.

M on right segment
[6,0,1,2,3,4,5]
 L     M     R
if nums[L]> nums[m] (means we are on the right segment). If the target is bounded at the right segment, look there.
                                                         nums[M] < target && target <= nums[R], look right
                                                         otherwise look left.


*/

#include <vector>

class Solution {
public:
    auto search(const std::vector<int>& nums, int target) -> int
    {
        auto L = 0;
        auto R = static_cast<int>(nums.size()-1);

        while(L <= R)
        {
            const auto M = (L+R)/2;
            if(nums[M] == target)
            {
                return M;
            }
            else if(nums[L] < nums[R]) // not rotated
            {
                if(target < nums[M])
                {
                    R = M-1; // Look left
                }
                else
                {
                    L = M+1; // Look right
                }
            }
            else if(nums[L] <= nums[M]) // M on left segment - ALWAYS REMEMBER <= because L and M can be on the same index!!!
            {
                if(nums[L] <= target && target < nums[M]) // If the target is bounded by the left segment, then search there
                {
                    R = M-1; // Look left
                }
                else
                {
                    L = M+1; // Look right
                }
            }
            else //if(nums[L] > nums[M]) // smaller values are to the left of M, since M is on the right segment
            {
                if(nums[M] < target && target <= nums[R]) // If the target is bounded at the right segment, look there.
                {
                    L = M+1;
                }
                else
                {
                    R = M-1;
                }
            }
        }
        return -1;
    }
};

auto main(int argc, char* argv[]) -> int
{
    //auto iii = Solution{}.search({3,1},1); // L and M are on the same index, I needed to do <=

    //auto iii = Solution{}.search({3,5,1},3); // This made me realise that I got the "on left segment" inner condition wrong.

    //auto iii = Solution{}.search({5,1,3},5);// This made me realise that I got the "on right segment" inner condition wrong.

    auto iii = Solution{}.search({4,5,6,7,8,1,2,3},8);


    return 0;
}
