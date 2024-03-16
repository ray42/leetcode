/*
MEDIUM https://leetcode.com/problems/product-of-array-except-self/

------------------------------------------------

RayNotes:

Solution 1

If we do a prefix product from left and right of nums, then we can do a final loop
and use the two vector of products to construct the final vector. E.g.
nums            = [1, 2, 3, 4]
Prefix  (left)  = [1, 2, 6, 24]
PostFix (right) = [24,24,12,4]

The ith entry of the answer would be L[i-1] * R[i+1], since that will miss out the middle entry.

-------------------------------------------------

Solution 2

We can improve upon the above solution, let's write out the answer symbolically for 
                   0  1  2  3
nums            = [1, 2, 3, 4]
Prefix  (left)  = [1, 2, 6, 24]
PostFix (right) = [24,24,12,4]
       0    1      2      3
ANS = [1*R1,L0*R2 ,L1*R3 ,L2*1]

As you can see, the entries follow a pattern. Let's split them up:

ANSL = [1 , L0, L1, L2]
ANSR = [R1, R2, R3, 1]

So we can loop through the array nums twice, once forward and once backwards
1) Create the entry in ANSL and put store it in the return array.
2) Create the entry in ANSR and multiply with the entry stored earlier, then store that instead.

See solution2 below
*/
#include <vector>
#include <type_traits>



class SolutionTemp {
public:
    auto productExceptSelf(std::vector<int>& nums) -> std::vector<int>
    {
        
    }
};




class Solution {
public:
    auto productExceptSelf(const std::vector<int>& nums) -> std::vector<int>
    {
        const auto numsSize = nums.size();

        // Calculate the prefix and postfix arrays
        auto prefix = std::vector<std::remove_cvref_t<decltype(nums)>::value_type>(numsSize);
        prefix[0] = nums[0];
        for(auto i = 1; i < numsSize; ++i)
        {
            prefix[i] = prefix[i-1]* nums[i];
        }

        auto postfix = std::vector<std::remove_cvref_t<decltype(nums)>::value_type>(numsSize);
        postfix[numsSize-1] = nums[numsSize-1];
        for(auto i = static_cast<int>(numsSize - 2); i >= 0; --i)
        {
            postfix[i] = postfix[i+1] * nums[i];
        }

        // Now we can calculate the productOfArrayExceptSelf
        auto productOfArrayExceptSelf = std::vector<std::remove_cvref_t<decltype(nums)>::value_type>(numsSize);

        // Handle the first and last separately
        productOfArrayExceptSelf[0] = postfix[1];
        productOfArrayExceptSelf[numsSize - 1] = prefix[numsSize - 2];
        // Handle the entries in between the first and last.
        for(auto i = 1; i < numsSize-1; ++i)
        {
            productOfArrayExceptSelf[i] = prefix[i-1] * postfix[i+1];
        }
        return productOfArrayExceptSelf;
    }
};

class Solution2 {
public:
    auto productExceptSelf(const std::vector<int>& nums) -> std::vector<int>
    {
        const auto numsSize = nums.size();

        auto ans = std::vector<std::remove_cvref_t<decltype(nums)>::value_type>(numsSize);
        
        // Create the entries in the prefix array (e.g. ANSL = [1 , L0, L1, L2]) and 
        // store it in ans
        ans[0] = 1;
        ans[1] = nums[0]; // L0 = nums0 by definition

        //                   0  1  2  3
        //nums            = [1, 2, 3, 4]
        //Prefix  (left)  = [1, 2, 6, 24]
        //PostFix (right) = [24,24,12,4]
        for(auto i = 2; i < numsSize; ++i)
        {
            ans[i] = ans[i-1]*nums[i-1]; // L0 is in ans[i-1], not ans[i-2]
        }

        // Now do the postfix entries ANSR = [R1, R2, R3, 1]
        ans[numsSize - 1] = ans[numsSize - 1] * 1;
        ans[numsSize - 2] = ans[numsSize - 2] * nums[numsSize - 1]; // R3 is the last entry of nums by definition

        // We need this to store the previous postfix because ans[i+1] is overwritten 
        auto previousEntry = nums[numsSize - 1];
        for(auto i = static_cast<int>(numsSize - 3); i >= 0; --i)
        {
            auto currentPostFix = nums[i+1] * previousEntry;
            ans[i] = ans[i] * currentPostFix;
            previousEntry = currentPostFix;
        }

        return ans;
    }
};

auto main(int argc, char*argv[])->int
{
    Solution{}.productExceptSelf({1,2,3,4});
    return 0;
}

