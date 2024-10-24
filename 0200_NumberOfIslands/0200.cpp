/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

------------------------

Solution:

To identify the number of island, we can loop through all the coordinates and do two things:
1) If it contains a 1 and is not visited before, then we have found a new island:
  1.1) increase the number of islands and add this coordinate and all coordinates that has a 1 and can be visited by this coordinate as visited.
2) If it contains a 0 or is visited, then just skip.

Once we have found an island, how do we mark it as visited? There are a few ways, I will implement them all:

1) Recursive DFS
2) Iterative DFS
3) Iterative BFS

4) Union Find - maybe this one doesn't belong in this list, but it should be possible to implement this using union find.


*/

#include <vector>
#include <stack>
#include <queue>
#include <utility>

class SolutionRecursiveDfs {
public:
    auto numIslands(std::vector<std::vector<char>>& grid) -> int
    {
        
        // Loop through all the grid cells
        const auto nRow = std::ssize(grid);
        const auto nCol = std::ssize(grid[0]); // This is OK since we know that the size of the grid is never 0

        auto nIslands = int{};

        // Mark every cell with a 1 reachable from r,c as visited (v), in a recursive DFS manner.
        auto visit = [&](auto&& visit, decltype(nRow) r, decltype(nCol) c)
        {
            // Cannot go out of bounds,go on a visited or 0
            if(r < 0 || c < 0 || r == nRow || c == nCol || grid[r][c] == 'v' || grid[r][c] == '0')
            {
                return ;
            }

            // Otherwise, mark this cell as visited and go in all four directions (top, bot, right, left)
            grid[r][c] = 'v';

            visit(visit, r, c + 1);
            visit(visit, r, c - 1);
            visit(visit, r + 1, c);
            visit(visit, r - 1, c);
        };

        for(auto r = decltype(nRow){}; r < nRow; ++r)
        {
            for(auto c = decltype(nCol){}; c < nCol; ++c)
            {
                // This is a new island? New islands are 1s which we have not visited and are not 0
                // visited are cells marked with v
                // Note: before, I had && grid[r][c] != 'v' && grid[r][c] != '0' in here, but I realised that I don't need it.
                // if grid[r][c] == 1, then it must be a NEW island, otherwise, we would have marked it as v in the visit function
                if(grid[r][c] == '1')
                {
                    visit(visit, r,c);
                    ++nIslands;
                }
            }
        }

        return nIslands;
    }
};


class SolutionIterativeDfs {
public:
    auto numIslands(std::vector<std::vector<char>>& grid) -> int
    {
        // Loop through all the cells and if it's not visited, mark them as visited
        // and increment the number of islands.

        static auto directions = std::vector<std::pair<int,int>>{
            {1,0},  // down
            {-1,0}, // up
            {0,1},  // right
            {0,-1}  // left
        };

        auto nRows = std::ssize(grid);
        auto nCols = std::ssize(grid[0]);

        auto visitViaIterativeDfs = [&](int r, int c)
        {
            // In DFS, we visit the children first, so we use a stack.
            auto stack = std::stack<std::pair<int,int>>{};

            // Only valid cells will be added to the stack, so we need to mark them as visited.
            stack.push({r,c});
            grid[r][c] = '0'; // We use 0 to denote visited, this is OK because in this context, a visited cell cannot be traveled on, it is essentially 0.

            while(!stack.empty())
            {
                const auto [rr,cc] = stack.top();
                stack.pop();

                for(const auto& [dr, dc] : directions)
                {
                    const auto rrdr = rr + dr;
                    const auto ccdc = cc + dc;
                    if(rrdr < 0 || ccdc < 0 || rrdr >= nRows || ccdc >= nCols || // Is it out of bounds?
                      grid[rrdr][ccdc] == '0') // Is is marked as 0?
                    {
                        continue;
                    }

                    // Otherwise, we can reach this cell from rr,cc. Let's mark it as visited and pop it in the stack.
                    stack.push({rrdr,ccdc});
                    grid[rrdr][ccdc] = '0';
                }
            }
        };


        auto nIslands = int{};

        for(auto r = decltype(nRows){}; r < nRows; ++r)
        {
            for(auto c = decltype(nCols){}; c < nCols; ++c)
            {
                if(grid[r][c] == '1')
                {
                    visitViaIterativeDfs(r,c);
                    ++nIslands;
                }
            }
        }

        return nIslands;
    }
};

class SolutionIterativeBfs {
public:
    auto numIslands(std::vector<std::vector<char>>& grid) -> int
    {
        

        const auto nrow = std::ssize(grid);
        const auto ncol = std::ssize(grid[0]);

        static auto directions = std::vector<std::pair<int,int>>{
            {1,0}, // down
            {-1,0}, // up
            {0,1}, // right
            {0,-1}, // left
        };

        auto visitViaIterativeBfs = [&](int r, int c){
            auto q = std::queue<std::pair<int,int>>{};

            q.push({r,c});
            grid[r][c] = '0'; // mark as visited

            while(!q.empty())
            {
                const auto [rr,cc] = q.front();
                q.pop();

                // Check in all directions and push cells with 1 reachable from here onto the stack.
                // mark them as visited, since once they are on the stack, they are visited (or we can say once we pop it, they are visited, but that will require slightly different code)
                for(const auto [dr,dc] : directions)
                {
                    auto rrdr = rr+dr;
                    auto ccdc = cc+dc;
                    if(rrdr < 0 || ccdc < 0 || rrdr == nrow || ccdc == ncol || grid[rrdr][ccdc] == '0')
                    {
                        continue;
                    }

                    q.push({rrdr,ccdc});
                    grid[rrdr][ccdc] = '0';
                }
            }




        };

        auto nIslands = 0;
        for(auto r = 0; r < nrow; ++r)
        {
            for(auto c = 0; c < ncol; ++c)
            {
                if(grid[r][c] == '1')
                {
                    visitViaIterativeBfs(r,c);
                    ++nIslands;
                }
            }
        }

        return nIslands;

    }
};


auto main(int argc, char* argv[]) -> int
{
    auto grid = std::vector<std::vector<char>>{
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'},
    };

    auto grid2 = std::vector<std::vector<char>>{
            {'0','1','0'},
            {'1','0','1'},
            {'0','1','0'}
            };

    auto iii = SolutionIterativeDfs{}.numIslands(grid);
    auto ii = 42;
    return 0;
}

