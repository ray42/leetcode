/*
You are a hiker preparing for an upcoming hike. 
You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). 
You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Example:

Input: heights = 
[[1*,2, 2],
 [3*,8, 2],
 [5*,3*,5*]]

The * denotes the path to take.

Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

#######################################################################

The answer is to use a modified Dijstras algorithm but let's see if we can figure this out on our own.

We know that we have to go from the top left to the bottom right and we want to know the minimum effort to get there.

Brute Force: Travel all routes via DFS and keep track of the minimum effort. If a route is greater than the current minimum effort, 
then we can backtrack and try other routes.

Why is this not good? We might end up trying all routes because the one with the minimum effort might be the last route we try.


Can we do it via BFS?

#######################################################################

BFS method:

What if we perform a BFS search. And at each step, we need the next cell to include is the one which increases the effort the least.

Is there any problem with this? Is it possible that we go on a cell which is required for the optimal solution at a later stage?

E.g.
heights = 
[[(1), 2 ,(1*),(1),(1)],
 [(1), 2 ,(1),  2, (1)],
 [(1), 2 ,(1),  2, (1)],
 [(1), 2 ,(1),  2, (1)],
 [(1),(1),(1),  2, (1)]]

[[(1), 1 ,(1*),(2),(1)],
 [(1), 2 ,(1),  3, (1)],
 [(1), 2 ,(1),  3, (1)],
 [(1), 2 ,(1),  3, (1)],
 [(1),(1),(1),  3, (1)]]

Is it possible that we somehow travel to the (1*) before we reach it via the optimal path and so we cannot include it in the optimal path?

I'm going to argue no. Why is that? Because if we reach (1*) for the first time, we did so because that path gives the minimum effort so far.

If later on we wanted to go to include (1*) in a path, then it cannot mean that our effort is lower, because we reached (1*) earlier, 
and earlier means lower or equal effort. The only other thing it can mean is that our current effort is equal to the effort when we reached (1*) the first time.



Let's say we have something like this:
[[(1),(1),(1), 2, 1],
 [ 1 , 2 , 1 , 3, 1],
 [ 1 , 2 , 1 , 3, 1],
 [ 1 , 2 , 1 , 3, 1],
 [ 1 , 1 , 1 , 3, 1]]

Just by looking at this, we know that we have to go to the 2 on the right, and then down:
[[(1),(1),(1), (2), (1)],
 [ 1 , 2 , 1 ,  3,  (1)],
 [ 1 , 2 , 1 ,  3,  (1)],
 [ 1 , 2 , 1 ,  3,  (1)],
 [ 1 , 1 , 1 ,  3,  (1)]]

But the BFS algorithm will go on the cells with smallest effort first:
[[(1),(1),(1), 2, 1],
 [(1), 2 ,(1), 3, 1],
 [(1), 2 ,(1), 3, 1],
 [(1), 2 ,(1), 3, 1],
 [(1),(1),(1), 3, 1]]

 Now if we are lucky, we might take the 2 on the top right, but we could easily go on the middle 2s first:
[[(1),(1),(1), 2, 1],
 [(1),(2),(1), 3, 1],
 [(1),(2),(1), 3, 1],
 [(1),(2),(1), 3, 1],
 [(1),(1),(1), 3, 1]]

Now finally we go on 2, then the 1s:
[[(1),(1),(1),(2),(1)],
 [(1),(2),(1), 3, (1)],
 [(1),(2),(1), 3, (1)],
 [(1),(2),(1), 3, (1)],
 [(1),(1),(1), 3, (1)]]

I guess that's the problem. It's still better than doing DFS and backtracking.

If we implement BFS via a priority queue, the complexity will be
1) Insert into heap - log(nm), where n, m is the number of rows and cols.
2) Dijstras complexity is V^2logV (or E log V), where V^2 is the max number of edges. So it could be
   (mn)^2 log V. However, how many edges are there? Each node can be connected to at most 4 other nodes.
   Thus, E = 4mn. Thus, the complexity is 
   O(4mnlog(mn)) = O(mnlog(mn) ).


What is the complexity of the DFS method? A big upper bound would be 2^(MN), which is every combination of paths we could have.


*/

#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>

class Solution {
public:
    auto minimumEffortPath(const std::vector<std::vector<int>>& heights) -> int
    {
        // Use a min heap to perform the BFS.
        // std::tuple<int,int,int> = effort, row index, col index.
        auto pq = std::priority_queue<std::tuple<int,int,int>, std::vector<std::tuple<int,int,int>>, std::greater<>>{};

        // top left with an effort of 0.
        pq.push({0,0,0});

        auto directions = std::vector<std::pair<int,int>>{
            {0,-1}, // left
            {0,1},  // right
            {-1,0}, // up
            {1,0}}; // down

        auto pairHash = [](const std::pair<int,int>&p){
            auto hasher = std::hash<int>{};
            auto seed = hasher(p.first);

            seed ^= hasher(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        };

        auto visited = std::unordered_set<std::pair<int,int>,decltype(pairHash)>{};

        const auto nrow = std::ssize(heights);
        const auto ncol = std::ssize(heights[0]);

        while(!pq.empty())
        {
            auto [effort, row, col] = pq.top();
            pq.pop();

            if(visited.contains({row,col}))
            {
                continue;
            }

            visited.insert({row,col});
            
            if(row == nrow - 1 && col == ncol -1)
            {
                return effort;
            }

            const auto currentHeight = heights[row][col];
            for(const auto [dr,dc] : directions)
            {
                auto newRow = row + dr;
                auto newCol = col + dc;

                // check bounds and not visited
                if(newRow < 0 || newRow == nrow || newCol < 0 || newCol == ncol || visited.contains({newRow,newCol}))
                {
                    continue;
                }

                auto newEffort = std::max(effort, std::abs(currentHeight- heights[newRow][newCol]));
                pq.push({newEffort,newRow,newCol});
            }
        }

        return -1;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto in1 = std::vector<std::vector<int>>
    {{1,2,2},
     {3,8,2},
     {5,3,5}};

     Solution{}.minimumEffortPath(in1);

    return 0;
}

