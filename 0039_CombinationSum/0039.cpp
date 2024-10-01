/*
So, given candidates = [1,2,3,4]

find all combinations and where the sum is equal to num is equal to target, we push it into the result.
See LC78 Subsets for how to calculate all subsets/combinations
If sum >= num, we can return right away, because the numbers in candidates are 
Maybe we can even avoid having to calculate the sum from scratch at each level 




*/

#include <vector>

class Solution {
public:
    auto combinationSum(const std::vector<int>& candidates, const int target) -> std::vector<std::vector<int>>
    {
        auto currentCombination = std::vector<int>{};
        auto resultCombinations = std::vector<std::vector<int>>{};
        const auto numCandidates = std::ssize(candidates);
        auto backtrack = [&candidates, &target, &numCandidates, &currentCombination, &resultCombinations](auto&& backtrack, const int i, const int currentSum){

            if(currentSum == target)
            {
                resultCombinations.push_back(currentCombination);
                return ;
            }
            if(i > numCandidates || currentSum > target)
            {
                
                return ;
            }

            // Keep adding the current number
            currentCombination.push_back(candidates[i]);
            backtrack(backtrack, i, currentSum + candidates[i]);
            currentCombination.pop_back();

            // Move onto the next number
            backtrack(backtrack, i+1, currentSum);

        };
        
        backtrack(backtrack, 0, 0);

        return resultCombinations;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.combinationSum({2,3,6,7},7);

    //auto iii = Solution{}.combinationSum({1,2},2);

    auto iiiii = 54;
    auto iiiiii = 54;
    auto iiiiiii = 54;

    return 0;
}
