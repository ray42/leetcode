
/*
Note: this is almost exactly the same as https://leetcode.com/problems/number-of-islands/description/
*/

#include <vector>
#include <queue>
#include <utility>

class Solution {
public:
    auto maxAreaOfIsland(std::vector<std::vector<int>>& grid) -> int
    {
        const auto nrow = std::ssize(grid);
        const auto ncol = std::ssize(grid[0]);

        static auto directions = std::vector<std::pair<int,int>>{
            {1,0},
            {-1,0},
            {0,1},
            {0,-1},
        };

        // visit using iterative bfs
        auto visit = [&](int r, int c) -> int
        {
            auto queue = std::queue<std::pair<int,int>>{};

            
            queue.push({r,c});
            grid[r][c] = 0;
            auto area = 1;

            while(!queue.empty())
            {
                // pop from the queue and check in all directions reachable from here.
                const auto [rr,cc] = queue.front();
                queue.pop();

                for(const auto&[dr,dc] : directions)
                {
                    const auto rrdr = rr+dr;
                    const auto ccdc = cc+dc;
                    if(rrdr < 0 || ccdc < 0 || rrdr == nrow || ccdc == ncol || grid[rrdr][ccdc] == 0)
                    {
                        continue;
                    }

                    queue.push({rrdr,ccdc});
                    grid[rrdr][ccdc] = 0;
                    ++area;
                }
            }
            return area;
        };

        auto maxArea = 0;
        for(auto r = 0; r < nrow; ++r)
        {
            for(auto c = 0; c < ncol; ++c)
            {
                if(grid[r][c] == 1)
                {
                    maxArea = std::max(maxArea,visit(r,c));
                }
            }
        }

        return maxArea;
        
    }
};


auto main(int argc, char* argv) -> int
{
    return 0;
}
