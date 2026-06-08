/*
https://leetcode.com/problems/rotting-oranges/description/

You are given an m x n grid where each cell can have one of three values:

    0 representing an empty cell,
    1 representing a fresh orange, or
    2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

Example 1:

Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.

------------------------------------------------------------------------------------------

1) We just need to run BFS once.
2) We'll start the BFS at all rotten oranges(i.e. push all the (i , j) pairs of rotten oranges initially in the Queue).
3) Since we can modify the grid, no need to keep a map to track visited elements. We'll just marked visited elements as rotten (i.e. mark with 2).
4) Each fresh orange will be reached by its closest rotten orange due to BFS.
5) In step 2, we keep a count of all the non-rotten oranges, and each time we visit a fresh orange, we decrement this counter.
   At the end, if this counter is greater than 0, there are fresh un-reachable oranges left so we return -1.
   Otherwise, return the number of BFS "levels" as the time it takes to make the whole board rotten.
*/

#include <vector>
#include <queue>


class Solution {
public:
    auto orangesRotting(std::vector<std::vector<int>>& grid) -> int
    {
        auto queue = std::queue<std::pair<int,int>>{};

        auto nrow = std::ssize(grid);
        auto ncol = std::ssize(grid[0]);

        // Put all rotten oranges in the queue and count how many fresh oranges there are.
        auto nFreshOranges = int{};
        for(auto r = decltype(nrow){}; r < nrow; ++r)
        {
            for(auto c = decltype(ncol){}; c < ncol; ++c)
            {
                if(grid[r][c] == 2)
                {
                    queue.push({r,c});
                }
                else if(grid[r][c] == 1)
                {
                    ++nFreshOranges;
                }
            }
        }

        // This means that there are no fresh oranges at time 0, and the problem statement is:
        // 
        if(nFreshOranges == 0)
        {
            return 0;
        }

        // Now use multi-source BFS and count the "levels".

        // We start counting the levels at -1 because we want the initial state to be 0 minutes
        static auto directions = std::vector<std::pair<int,int>>{
            {-1,0}, // up
            {1,0},  // down
            {0,-1}, // left
            {0,1},  // right
        };
        auto nBfsLevels = -1;
        while(!queue.empty())
        {
            const auto queueSize = std::ssize(queue);

            // Note: The first time this is entered, this could be 0 minutes.
            // If we have 2 oranges next to each other, and one of them is initially rotten
            // then we want the final number of minutes to be 1. Doing it this way gives us this result.
            ++nBfsLevels;
            for(auto i = 0; i < queueSize; ++i) // Loop through all the cells in this level.
            {
                // pop the cell and push all it's neighbour fresh oranges into the queue.
                // We have to remember mark the ones we push as rotten because when we pop them, we don't want to travel toa  neighbour that is already in the queue.
                const auto [r,c] = queue.front();
                queue.pop();

                // Visit the neighbours
                for(const auto [dr,dc] : directions)
                {
                    const auto cr = r+dr; // current row
                    const auto cc = c+dc; // current col
                    // Check if it's in bound, then check if it's a fresh orange
                    if(cr < 0 || cc < 0 || cr == nrow || cc == ncol || grid[cr][cc] != 1)
                    {
                        continue;
                    }
                    queue.push({cr,cc});
                    grid[cr][cc] = 2;
                    --nFreshOranges;
                }
            }
        }

        // If nFreshOranges == 0, it means all the oranges have been reached.
        return nFreshOranges == 0 ? nBfsLevels : -1;
    }
};



auto main(int argc, char* argv[]) -> int
{
    return 0;
}
