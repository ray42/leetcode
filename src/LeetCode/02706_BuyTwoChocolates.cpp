/*
EASY: https://leetcode.com/problems/buy-two-chocolates

*/
#include <vector>
#include <algorithm>

class SolutionUsingSort {
public:
    auto buyChoco(std::vector<int>& prices, int money) -> int
    {
        // nlogn solution
        std::ranges::sort(prices);

        auto leftOver = money - prices[0] - prices[1];
        return leftOver >= 0 ? leftOver : money;
    }
};

class SolutionOnePass {
public:
    auto buyChoco(std::vector<int>& prices, int money) -> int
    {
        auto smallest = INT_MAX;
        auto secondSmallest = INT_MAX;
        for(const auto& p : prices)
        {
            if(p < smallest)
            {
                secondSmallest = smallest;
                smallest = p;
            }
            else if(p < secondSmallest)
            {
                secondSmallest = p;
            }
        }

        auto leftOver = money - smallest - secondSmallest;
        return leftOver >= 0 ? leftOver : money;
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}
