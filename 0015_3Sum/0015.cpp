#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>


#include "headertest.hpp"


class Solution {
public:
    auto threeSum(std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        // Sort the array
        // Fix the 
        return {};
    }
};





// This is wrong - times out. Find out the better way to do it above.
class SolutionWrong {
public:
    auto threeSum(std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        auto hash = [](const std::vector<int>& v){
            auto hasher = std::hash<int>{};
            auto seed = std::size_t{};
            for(const auto i : v)
            {
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        };
        auto triplets = std::unordered_set<std::vector<int>, decltype(hash)>{};

        auto numsSize = nums.size();
        for(auto k = 0; k < numsSize; ++k)
        {
            // Now do 2 sum
            const auto target = -nums[k];
            
            auto complements = std::unordered_map<int,int>{};
            for(auto i = k+1; i < numsSize; ++i)
            {
                const auto& val = nums[i];
                const auto& compliment = target - val;

                if(auto it = complements.find(compliment); it != complements.end())
                {
                    // Now we need to sort the values and stick it in triplets.
                    // Also, we should put "it" into complements in case it's a complement for something else.
                    // Since we need to find ALL pairs.
                    auto triplet = std::vector<int>{nums[k], val, it->first};
                    std::ranges::sort(triplet);

                    triplets.insert(triplet);
                }

                complements.insert({val, i});
            }
        }

        auto ret = std::vector<std::vector<int>>(triplets.begin(), triplets.end());
        return ret;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto tc = TestClass{};
    
    std::cout << tc.addAuto(5,2) << '\n';

    //std::cout << tc.addNoTemplate(2,3) << '\n';
    return 0;
}

