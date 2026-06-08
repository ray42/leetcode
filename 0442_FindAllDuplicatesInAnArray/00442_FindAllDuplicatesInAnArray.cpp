
#include <vector>
#include <type_traits>

/*
The trick to do this in constant time is to observe the constraints:
Constraints:
    n == nums.length
    1 <= n <= 105
    1 <= nums[i] <= n
    Each element in nums appears once or twice.

    So we know that the numbers in the array cannot be greater than the
    length if the array and is greater than one. That is, this constraint:
    1 <= nums[i] <= n 
    basically tells is that we can use the array positions as markers.
    But how? It's easy, we just make the value in the array as 
    negative as we talk across it.
    E.g. if the array is of length 3, then we know that the values in
    num can only be 1,2 or 3. Say it's nums = [1,2,3], then we loop
    through nums and the index will be "abs(val)-1". If the value at "abs(val)-1"
    is negative, then we know that we have seen it already and add it to the 
    vector.
    Why does it have to be abs(val) - 1? Because val would have already
    been turned negative and we need to -1 since the range is
    1 <= nums[i] <= n and the index of nums is 0<=index<=n-1.
*/
class Solution {
public:
    auto findDuplicates(std::vector<int>& nums) -> std::vector<int>
    {
        auto ans = std::vector<std::remove_cvref_t<decltype(nums)>::value_type>{};
        for(const auto& val : nums)
        {
            auto absVal = std::abs(val);
            if(nums[absVal - 1] < 0)
            {
                ans.push_back(absVal);
            }
            else
            {
                // This is key because we do not want to put in absVal * -1, because 
                // absVal -1 is the index, we actually just want to turn the value in the
                // index negative. We don't know/care what value is in the index
                nums[absVal - 1] *= -1; 
            }
        }
        return ans;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto iii = std::vector<int>{4,3,2,7,8,2,3,1};
    auto ii = Solution{}.findDuplicates(iii);
    return 0;
}

