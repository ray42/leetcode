#include <vector>

class Solution {
public:
    auto threeConsecutiveOdds(const std::vector<int>& arr) -> bool
    {
        auto consecutiveOddCount = 0;
        for(auto a : arr)
        {
            // Odd detected
            if(a&1)
            {
                // Optimisation, we know if consecutiveOddCount == 2, then it's about to be 
                // incremented to 3, we can return true before even incrementing.
                if(consecutiveOddCount == 2)
                {
                    return true;
                }
                consecutiveOddCount++;
            }
            else
            {
                // Even so reset
                consecutiveOddCount = 0;
            }
        }
        return false;
    }
};