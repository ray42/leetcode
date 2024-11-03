


#include <vector>
#include <queue>
#include <unordered_set>
#include <utility>
#include <array>
#include <cassert>

/*
This is not a multi source BFS because each flow of water from a source is considered different
 - cells reached from one source might not be reached from other sources. That's the whole point :)


 Plan of attack:
 Loop through all cells
   Perform BFS on each cell
   If the BFS reaches any cells with r = 0 OR c = 0 (pacific ocean) AND r = nrow-1 OR c = ncol-1 (atlantic ocean) - insert it into the vector and return.

-----------------------------

IMPORTANT: there is something buggy about the below implementation, HOWEVER, I've realised that it's also VERY inefficient.
Why? Because we are performing BFS on each cell. HOWEVER, say the water flows like:
this way ->[1,2,3,4], so water flows from cell 1 to cell 4. Then we check if water can flow from cell 2 to cell 4. Then we check if water can flow from cell 3 to cell 4.
But we know all this by checking if water can flow from cell 1 to cell 4 because it passes through 2 and 3 to get to 4.

Look at the below solution for the correct way to do it.
*/
class SolutionWrong
{

public:

    struct PairHash
    {
        inline std::size_t operator() (const std::pair<int,int>& c) const
        {
            return c.first*31+c.second;
        }
    };

    auto pacificAtlantic(std::vector<std::vector<int>>& heights) -> std::vector<std::vector<int>>
    {
        const auto nrow = std::ssize(heights);
        const auto ncol = std::ssize(heights[0]);

        auto directions = std::vector<std::pair<int,int>>
        {
            {-1,0},
            {1,0},
            {0,-1},
            {0,1},
        };

        auto isOnTopOrLeft = [&](int r, int c) -> bool
        {
            if(r == 0 || c == 0)
            {
                return true;
            }
            
            return false;
        };

        auto isOnBotOrRight = [&](int r, int c) -> bool
        {
            if(r == nrow - 1 || c == ncol - 1)
            {
                return true;
            }
            
            return false;
        };

        auto canReachBothOceans = [&](int r, int c) -> bool
        {
            // Check if we need to do any work at all.
            if(isOnTopOrLeft(r,c) && isOnBotOrRight(r,c))
            {
                return true;
            }

            auto queue = std::queue<std::pair<int,int>>{};

            queue.push(std::pair{r,c});

            // To stop us flowing back into ourselves - creating an infinite loop
            auto visited = std::unordered_set<std::pair<int,int>, PairHash>{};
            visited.emplace(r,c);

            auto topLeftReached = false;
            auto botRightReached = false;

            while(!queue.empty())
            {
                // Use BFS to reach both oceans - since we don't care about "time" or "levels", we don't
                // need an additional loop to go from 0 to the size of the current queue to traverse all the 
                // nodes on that level.

                const auto [curr,curc] = queue.front();
                queue.pop();

                for(const auto[dr,dc] : directions)
                {
                    const auto newr = curr + dr;
                    const auto newc = curc + dc;

                    // Check if it's in bound, 
                    //   then check if we can flow into it.
                    //   if we can flow into it (if the value is equal to or less than the one at curr,curc), then add it to the queue and mark it as visited.
                    //   Now we should also check if this adjacent to an ocean - we need to continue until both oceans are reached.
                    if(newr < 0 || newc < 0 || newr == nrow || newc == ncol || visited.contains(std::pair{newr,newc}))
                    {
                        continue;
                    }

                    if(heights[newr][newc] <= heights[curr][curc])
                    {
                        queue.push(std::pair{newr,newc});
                        visited.emplace(newr,newc);

                        // Only check if it has not already been reached.
                        if(!topLeftReached)
                        {
                            topLeftReached = isOnTopOrLeft(newr,newc);
                        }

                        if(!botRightReached)
                        {
                            botRightReached = isOnBotOrRight(newr,newc);
                        }

                        if(topLeftReached && botRightReached)
                        {
                            return true;
                        }
                    }
                }

            }

            return false;
        };

        auto res = std::vector<std::vector<int>>{};
        for(auto r = int{}; r < nrow; ++r)
        {
            for(auto c = int{}; c < ncol; ++c)
            {
                if(canReachBothOceans(r,c))
                {
                    res.push_back({static_cast<int>(r),static_cast<int>(c)});
                }
            }
        }

        return res;
    }
};


/*
Here, we do the more optimised solution. Instead of going through every cell on the grid and working out if water can flow to both oceans...
We do it in reverse. We run multi-source BFS twice:
1) Once from all cells on the left and top.
2) Another time from all the cells on the bottom and right.

Water can flow "backwards" from cell A to cell B if the value of A is less and or equal to B.

In both BFSs, we keep track of the visited cells (using two separate grids, one for each BFS).

Finally, we loop through all the cells in both and return a vector of the cells that are visited in both grids.

Instead of using two visited grid, we can use one and have a bit field.
*/
class Solution {
public:

    enum options : int
    {
        M_TOP_LEFT_REACHED = 1u << 0,
        M_BOT_RIGHT_REACHED = 1u << 1,
    };

    auto pacificAtlantic(std::vector<std::vector<int>>& heights) -> std::vector<std::vector<int>>
    {
        const auto nrow = heights.size();
        const auto ncol = heights[0].size();

        auto visited = std::vector<std::vector<int>>(heights.size(),std::vector<int>(heights[0].size()));
        
        // Do BFS from all cells in top left
        auto queue = std::queue<std::pair<int,int>>{};
        
        // Insert all cells from left and top
        auto c = 0;
        for(auto rr = 0; rr < nrow; ++rr)
        {
            queue.push({rr,c});
            visited[rr][c] |= M_TOP_LEFT_REACHED;
        }
        auto r = 0;
        // c == 0 is covered by the above, but it doesn't matter if we insert it in twice
        // because we are using this in a multi source bfs, so for repeated nodes,
        // the algorithm will try to visit the nodes already visited (which it can't), 
        // then move on
        for(auto cc = 0; cc < ncol; ++cc)
        {
            queue.push({r,cc});
            visited[r][cc] |= M_TOP_LEFT_REACHED;
        }

        auto directions = std::vector<std::pair<int,int>>{
            {-1,0}, // up
            {1,0},  // down
            {0,-1}, // left
            {0,1},  // right
        };
        // Now perform BFS
        auto bfs = [&](int sideToCheck){

            while(!queue.empty())
            {
                const auto [currentR, currentC] = queue.front();
                queue.pop();
                for(const auto[dr,dc] : directions)
                {
                    const auto newR = currentR + dr;
                    const auto newC = currentC + dc;

                    // Check if it's in bound and not visited.
                    if(newR < 0 || newC < 0 || newR == nrow || newC == ncol || (visited[newR][newC] & sideToCheck))
                    {
                        continue;
                    }

                    // Now check if new cell is viable for water to flow "backwards", i.e. it has to be equal to or greater than the current cell.
                    if(heights[newR][newC] >= heights[currentR][currentC])
                    {
                        // Put it in the queue and mark it as visited
                        queue.push({newR,newC});
                        visited[newR][newC] |= sideToCheck;
                    }
                    
                }
            }
        };

        bfs(M_TOP_LEFT_REACHED);

        // The queue should now be empty.
        assert(queue.empty());

        // Now repeat but with the bot right
        
        // do bot
        r = nrow-1;
        for(auto cc = 0; cc < ncol; ++cc)
        {
            queue.push({r,cc});
            visited[r][cc] |= M_BOT_RIGHT_REACHED;
        }
        // do right
        c = ncol-1;
        for(auto rr = 0; rr < nrow; ++rr)
        {
            queue.push({rr,c});
            visited[rr][c] |= M_BOT_RIGHT_REACHED;
        }
        bfs(M_BOT_RIGHT_REACHED);


        auto reachedBothOceans = std::vector<std::vector<int>>{};
        for(auto r = 0; r < heights.size(); ++r)
        {
            for(auto c = 0; c < heights[0].size(); ++c)
            {
                if((visited[r][c] & M_TOP_LEFT_REACHED) && (visited[r][c] & M_BOT_RIGHT_REACHED))
                {
                    reachedBothOceans.push_back({r,c});
                }
            }
        }

        return {};
    }
};




auto main(int argc, char* argv[]) -> int
{
    auto grid = std::vector<std::vector<int>>{
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    };


    return 0;
}
