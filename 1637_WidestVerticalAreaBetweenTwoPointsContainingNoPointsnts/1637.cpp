/*
MEDIUM: https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/description/

This problem statement is just sooo bad. It should be re-worded like this: 
Find largest horizontal distance between two adjacent points.
------------------------------
Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two points such that no points are inside the area.
A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height). The widest vertical area is the one with the maximum width.
Note that points on the edge of a vertical area are not considered included in the area.

Example 1:
​
Input: points = [[8,7],[9,9],[7,4],[9,7]]
Output: 1
Explanation: Both the red and the blue area are optimal.

Example 2:
Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
Output: 3

Constraints:

    n == points.length
    2 <= n <= 105
    points[i].length == 2
    0 <= xi, yi <= 109
------------------------------
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


