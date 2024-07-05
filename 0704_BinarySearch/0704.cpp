#include <vector>

class Solution {
public:
    auto search(const std::vector<int>& nums, const int target) -> int
    {
        auto lo = static_cast<int>(0);
        auto hi = static_cast<int>(nums.size()-1);
        auto mid = static_cast<int>(-1);
        while(lo <= hi)
        {
            mid = (lo + hi) / 2;

            if(target > nums[mid])
            {
                lo = mid + 1;
            }
            else if(target < nums[mid])
            {
                hi = mid - 1;
            }
            else
            {
                return mid;
            }
            
        }

        return -1;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.search({5}, 5);
    return 0;
}
