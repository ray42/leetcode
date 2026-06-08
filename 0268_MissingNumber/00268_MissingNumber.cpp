
#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingNumber(const std::vector<int>& nums) {
        auto unorderedSet = std::unordered_set<std::remove_cvref_t<decltype(nums)>::value_type>(nums.begin(),nums.end());
        for(const auto& n : nums)
        {
            if(!unorderedSet.contains(n))
            {
                return n;
            }
        }
        return -1;
    }
};


auto main(int argc, char* argv) -> int
{
    Solution{}.missingNumber({3,0,1});
    return 0;
}