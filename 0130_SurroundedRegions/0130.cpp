
#include <vector>
#include <unordered_set>
#include <queue>

/*
1. Go through each cell, if we find a O, start BFS
2. During the BFS, 
    mark every cell as visited so we don't start BFS on it again.
    temporarily store the cells of this region for easy access when we decide to capture the region.
    If at the end of the BFS, we've found an O on the edge of the square (at r==0, c==0, r==nrow-1 or c==ncol-1), then we cannot capture it. Otherwise, capture it.
    Note: We cannot end the BFS early when we have found that it's on an edge since 
      we need to mark ALL the cells in the region as visited to stop us performing BFS on (parts) of regions late on.

*/
class Solution {
public:
    
    auto solve(std::vector<std::vector<char>>& board) -> void
    {
        const auto nrow = std::ssize(board);
        const auto ncol = std::ssize(board[0]);

        static const auto directions = std::vector<std::pair<int,int>>{
            {-1,0},
            {1,0},
            {0,-1},
            {0,1},
        };

        auto pairHash = [](const std::pair<int,int>& p){
            auto seed = size_t{};
            auto hasher = std::hash<int>{};
            seed ^= hasher(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hasher(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            
            return seed;
        };

        auto visited = std::unordered_set<std::pair<int,int>, decltype(pairHash)>{};
        auto queue = std::queue<std::pair<int,int>>{};

        auto checkSetIsOnEdge = [&](int r, int c, bool& isOnEdge) -> void
        {
            // Only need to check if r,c are on edge if there had not been previously an r,c on edge.
            if(!isOnEdge && (r == 0 || c == 0 || r == nrow-1 || c == ncol-1))
            {
                isOnEdge = true;
            }
        };

        auto bfs = [&](int r, int c)
        {
            auto isOnEdge = false;
            auto tempCells = std::vector<std::pair<int,int>>{};

            queue.push({r,c});
            visited.insert({r,c});
            tempCells.emplace_back(r,c);
            checkSetIsOnEdge(r,c,isOnEdge);

            while(!queue.empty())
            {
                const auto [currentR, currentC] = queue.front();
                queue.pop();

                for(const auto [dR,dC] : directions)
                {
                    const auto newR = currentR + dR;
                    const auto newC = currentC + dC;

                    if(newR < 0 || newC < 0 || newR == nrow || newC == ncol || visited.contains({newR,newC}) || board[newR][newC] != 'O')
                    {
                        continue;
                    }

                    // We are on an O
                    queue.push({newR,newC});
                    visited.insert({newR,newC});
                    tempCells.emplace_back(newR,newC);
                    checkSetIsOnEdge(newR,newC,isOnEdge);
                }
            }

            // Can only capture if none of the Os on the region is on edge.
            if(!isOnEdge)
            {
                for(const auto[tempR,tempC] : tempCells)
                {
                    board[tempR][tempC] = 'X';
                }
            }
        };

        // Loop through and perform bfs
        for(auto r = 0; r < nrow; ++r)
        {
            for(auto c = 0; c < ncol; ++c)
            {
                if(board[r][c] == 'O' && !visited.contains({r,c}))
                {
                    bfs(r,c);
                }
            }
        }
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto board = std::vector<std::vector<char>>{
        {'O','O','O'},
        {'O','O','O'},
        {'O','O','O'}
    };

    Solution{}.solve(board);
    auto iii = 42;
    return 0;
}

