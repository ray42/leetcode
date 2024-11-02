
/*
// This is the same problem but from neetcode: https://neetcode.io/problems/islands-and-treasure

You are given a m x n 2D grid initialized with these three possible values.

    -1 - A wall or an obstacle.
    0 - A gate.
    INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.

Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example: 

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF

After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4


///////////////////////////////

My Solution:

So, the only way I see to do this is, loop through each cell, for each cells which is INF,
need to apply BFS to work out the shortest distance to a 0. 
    BFS is the most efficient method to work out the closest distance from a node to ALL nodes for an unweighted graph
    Once a 0 has been found, we can return the answer and move on to the next INF cell.

Cells which are -1 and 0 are kept as they are.

Space: O(1) if we can modify the original grid, otherwise O(MN)
Time: Looping through the grid: O(M*N), performing BFS O(4^(MN)) because there can be up to 4 choices, and there are M*N cells (depth)
      O(M*N*4^(M*N))
*/

#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>
#include <iostream>


// Note: I am using a C++11 solution because https://neetcode.io/problems/islands-and-treasure doesn't support anything else.
class Solution {
public:

     
    struct PairHash
    {
        inline std::size_t operator() (const std::pair<int,int>& c) const
        {
            return c.first*31+c.second;
        }
    };

    auto islandsAndTreasure(std::vector<std::vector<int>>& grid) -> void
    {
        const auto nrow = grid.size();
        const auto ncol = grid[0].size();

        static auto directions = std::vector<std::pair<int,int>>{
            {1,0},
            {-1,0},
            {0,1},
            {0,-1},
        };

        auto distanceToNearestGate = [&](int r, int c) -> int
        {
            // Use (iterative) BFS to reach the closest 0, return the distance.
            auto queue = std::queue<std::pair<int,int>>{};
            queue.push({r,c});
            auto visited = std::unordered_set<std::pair<int,int>, PairHash>{};

            auto distance = 0;

            while(!queue.empty())
            {
                const auto queueSize = queue.size();
                ++distance;
                for(auto i = 0; i < queueSize; ++i) // Loop through all the cells in this level.
                {
                    const auto currentPair = queue.front();
                    queue.pop();
                    // Assuming grid[r][c] is valid, we go in all four directions:
                    // if it's -1 or already visited, we can just discount it (continue with the next cell check)
                    // if it's INF, then we continue checking
                    // if it's 0, we return right away.
                    for(auto direction : directions)
                    {
                        // Work out the next cell and check if it's valid
                        const auto rrdr = currentPair.first + direction.first;
                        const auto ccdc = currentPair.second + direction.second;
                        
                        if(rrdr < 0 || rrdr == nrow || ccdc < 0 || ccdc == ncol ||
                           grid[rrdr][ccdc] == -1 || visited.find(std::pair<int,int>(rrdr,ccdc)) != visited.end())
                        {
                            continue;
                        }

                        if(grid[rrdr][ccdc] == 0)
                        {
                            return distance;
                        }
                        
                        // This must be a valid room, so just insert it into the queue.
                        queue.push(std::pair<int,int>(rrdr,ccdc));
                        visited.insert(std::pair<int,int>(rrdr,ccdc));
                    }
                }
            }

            // No gate '0' found, so return 2147483647
            return 2147483647;
        };

        for(auto r = int{}; r < nrow; ++r)
        {
            for(auto c = int{}; c < ncol; ++c)
            {
                if(grid[r][c] == 2147483647)
                {
                    grid[r][c] = distanceToNearestGate(r,c);
                }
            }
        }
    }
};



auto main(int argc, char* argv[]) -> int
{
    //auto grid = std::vector<std::vector<int>>
    //{{2147483647,        -1,         0,2147483647},
    // {2147483647,2147483647,2147483647,        -1},
    // {2147483647,        -1,2147483647,        -1},
    // {         0,        -1,2147483647,2147483647}};
//
    //Solution{}.islandsAndTreasure(grid);
//
    //auto iii = 42;

    std::cout << "Hello Ray" << std::endl;

    return 0;
}




