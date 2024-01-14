/*
Medium: https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/description/
*/
#include <vector>
#include <unordered_set>

class Solution {
public:
    auto findMatrix(const std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        // If there is are values, just return blank
        if(nums.empty()) return {};

        auto ans = std::vector<std::vector<int>>{};
        auto helper = std::vector<std::unordered_set<int>>{};

        for(const auto& n : nums)
        {
            auto inserted = false;

            for(auto i = 0; i < helper.size(); ++i)
            {
                if(auto [it, _inserted] = helper[i].emplace(n); _inserted)
                {
                    ans[i].push_back(n);
                    inserted = true;
                    break;
                }
            }

            if(!inserted)
            {
                ans.push_back(std::vector<int>{});
                ans.back().push_back(n);
                helper.push_back(std::unordered_set<int>{});
                helper.back().emplace(n);
            }
        }
        return ans;
    }
};


auto main(int argc, char * argv[]) -> int
{
    return 0;
}
