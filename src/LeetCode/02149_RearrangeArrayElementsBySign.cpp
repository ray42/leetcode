
#include <vector>

class Solution {
public:
    std::vector<int> rearrangeArray(const std::vector<int>& nums) 
    {
        // We know that positive must be first position.
        // Then followed by negative, etc...
        auto posPosition = 0;
        auto negPosition = 1;
        
        auto res = std::vector(nums.size(), 0);
        for(const auto n : nums)
        {
            if(n >= 0)
            {
                res[posPosition] = n;
                posPosition += 2;
            }
            else
            {
                res[negPosition] = n;
                negPosition += 2;
            }
        }

        return res;
    }
};

auto main(int argc, char* argv[]) -> int
{
    //Solution{}.rearrangeArray({3,1,-2,-5,2,-4});
    Solution{}.rearrangeArray({});
    return 0;
}
