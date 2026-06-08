/*
MEDIUM: https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/description/

This problem statement is just sooo bad. It should be re-worded like this: 
Find largest horizontal distance between two adjacent points.

*/
#include <algorithm>
#include <vector>

class Solution 
{
public:
    int maxWidthOfVerticalArea(std::vector<std::vector<int>>& points) 
    {
        std::ranges::sort(points, [](const auto& lhs, const auto& rhs){ return lhs[0] < rhs[0];});

        auto maxWidth = -1;
        for(auto i = 1; i < points.size(); ++i)
        {
            if(auto width = points[i][0] - points[i-1][0]; width > maxWidth)
            {
                maxWidth = width;
            }
        }
        return maxWidth;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}


