/*
You are given an nxn integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
The rain starts to fall. At time t, the depth of the water everywhere is t. 
You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. 
You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.

Return the least time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

Example 1:

Input: grid = 
[[0,2],
 [1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.

Example 2:

Input: grid = 
[[0* , 1*,2* ,3* ,4*],
 [24 ,23 ,22 ,21 ,5*],
 [12*,13*,14*,15*,16*],
 [11*,17 ,18 ,19 ,20],
 [10*,9* ,8* ,7* ,6*]]

Output: 16
Explanation: The final route is shown with *.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

############################################################################

OK, so we use Dijstras algorithm as explained in the NeetCode video.

It's important to realise what the question is really asking us to find.
It's asking us to find. We need to find the path from the top left to the bottom right which has the lowest maximum value.

E.g. Consider 
Input: grid = 
[[0,2],
 [1,0]]

To get from top left to the bottom right, there are two paths, 0-1-0 or 0-2-0. The maximum value of the paths are 1 and 2, and the minimum of those two is 1.
This is our answer, 1.

Write about how we use dijstras and about the functions to add the value into the min heap


*/


#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <utility>

class Solution {
public:

    struct PairHash
    {
        inline auto operator()(const std::pair<int,int>& p) const -> std::size_t
        {
            auto hasher = std::hash<int>{};
            auto seed = hasher(p.first);

            seed ^= hasher(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };

    auto swimInWater(const std::vector<std::vector<int>>& grid) -> int
    {
        const auto nrow = std::ssize(grid);
        const auto ncol = std::ssize(grid[0]);

        const static auto directions = std::array<std::pair<int,int>,4>{{
            {0,1}, // up
            {0,-1},// down
            {-1,0},// left
            {1,0}, // right
        }};

        auto minHeap = std::priority_queue<std::tuple<int,int,int>,std::vector<std::tuple<int,int,int>>,std::greater<std::tuple<int,int,int>>>{};
        
        // Start at the top left
        minHeap.push({grid[0][0],0,0}); // Grid value, row index, col index

        auto maxHeight = -1;
        auto visited = std::unordered_set<std::pair<int,int>,PairHash>{};

        while(!minHeap.empty())
        {
            auto [val, r, c] = minHeap.top();
            minHeap.pop();

            visited.insert({r,c});

            maxHeight = std::max(maxHeight, val);
            // Check if r and c are at the bottom right. If it is, then take the height again and break
            if(r == nrow -1 && c == ncol -1)
            {
                return maxHeight;
            }

            for(const auto [dr,dc] : directions)
            {
                auto newR = r + dr;
                auto newC = c + dc;
                if( newR < 0 || newR == nrow || newC < 0 || newC == ncol || visited.contains({newR,newC}))
                {
                    continue;
                }
                minHeap.push({grid[newR][newC],newR,newC});
            }
        }

        return 0;
    }
};


auto main(int argc, char* argv[])->int
{
    auto iii = Solution{}.swimInWater(std::vector<std::vector<int>>{});
    return 0;
}

