/*
Medium https://leetcode.com/problems/find-players-with-zero-or-one-losses/description/

Pretty simple...

*/

#include <vector>
#include <unordered_map>
#include <algorithm>


class Solution {
public:
    auto findWinners(const std::vector<std::vector<int>>& matches) -> std::vector<std::vector<int>>
    {
        auto lostFreq = std::unordered_map<int, int>{};
        for(const auto& match : matches)
        {
            if(auto it = lostFreq.find(match[0]); it == lostFreq.end())
            {
                lostFreq[match[0]] = 0;
            }
            
            ++lostFreq[match[1]];
        }

        auto winners = std::vector<std::vector<int>>{std::vector<int>{},std::vector<int>{}};
        for(const auto& [player, losses] : lostFreq)
        {
            if(losses == 0)
            {
                winners[0].push_back(player);
            }
            if(losses == 1)
            {
                winners[1].push_back(player);
            }
        }

        std::ranges::sort(winners[0]);
        std::ranges::sort(winners[1]);
        return winners;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
