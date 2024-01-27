/*
Easy https://leetcode.com/problems/baseball-game/
*/

#include <vector>
#include <string>
#include <functional> // for std::plus
#include <numeric>
#include <algorithm>
#include <cctype>

class Solution {
public:
    auto calPoints(std::vector<std::string>& operations) -> int
    {
        auto resVec = std::vector<int>{};
        for(const auto& op : operations)
        {
            if(op[0] == '+')
            {
                const auto lastPos = resVec.size()-1;
                resVec.push_back(resVec[lastPos] + resVec[lastPos-1]);
            }
            else if(op[0] == 'D')
            {
                const auto lastPos = resVec.size()-1;
                resVec.push_back(2*resVec[lastPos]);
            }
            else if(op[0] == 'C')
            {
                resVec.pop_back();
            }
            else
            {
                resVec.push_back(std::stoi(op));
            }
        }

        return std::accumulate(resVec.begin(), resVec.end(),0, std::plus<int>{});
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
