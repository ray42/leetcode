
#include <vector>

class Solution {
public:
    auto combine(const int n, const int k) -> std::vector<std::vector<int>>
    {
        auto resultCombinations = std::vector<std::vector<int>>{};

        auto currentCombination = std::vector<int>{};


        auto dfs = [&n, &k, &currentCombination, &resultCombinations](auto && dfs, int idx)
        {
            // Remember that this is N choose K, so if size(currentCombination) == k, we insert and return
            if(std::size(currentCombination) == k)
            {
                resultCombinations.push_back(currentCombination);
                return;
            }

            // idx starts at 1, so if idx > n, it means previously, we have considered n entries, so
            // checking beyond n makes no sense.
            if(idx > n)
            {
                return;
            }
            

            // Consider idx
            currentCombination.push_back(idx);
            dfs(dfs, idx + 1);

            // backtrack
            currentCombination.pop_back();

            dfs(dfs, idx + 1);
        };

        dfs(dfs, 1);

        return resultCombinations;


    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

