

#include <vector>
#include <type_traits>
#include <algorithm>
#include <ranges>

class Solution {
public:

    auto combinationSum2(std::vector<int>& candidates, int target) -> std::vector<std::vector<int>>
    {
        std::ranges::sort(candidates);
        
        auto allCombinations = std::vector<std::vector<std::remove_cvref_t<decltype(candidates)>::value_type>>{};
        auto currentCombination = std::vector<std::remove_cvref_t<decltype(candidates)>::value_type>{};
        const auto& numCandidates = std::ssize(candidates);

        auto dfs = [&](auto&& dfs, int idx, int currentSum)
        {
            if(currentSum == target)
            {
                allCombinations.push_back(currentCombination);

                return;
            }

            if(currentSum > target || idx >= numCandidates)
            {
                return;
            }

            // Choose number at idx
            currentCombination.push_back(candidates[idx]);

            // We cannot choose idx again at the next level since we cannot choose the same position more than once.
            // So we have to increment idx to choose the next one - the next one might be the same number as the current one.
            dfs(dfs, idx+1, currentSum + candidates[idx]);

            // backtrack
            currentCombination.pop_back();

            // Now we need to shift idx such that the number indexed by idx is not the same as the current number
            auto j = idx + 1;
            while(j < numCandidates && candidates[idx] == candidates[j]) ++j;

            // If j == numCandidates, we will not go out of bounds because it will be caught by the if statement.
            dfs(dfs, j, currentSum);
        };

        dfs(dfs, 0, 0);

        return allCombinations;
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}

