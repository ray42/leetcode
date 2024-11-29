/*
 This is exactly the same as 207 Course Schedule, but instead of returning true or false,
 we return the topological sort or empty array
*/

#include <vector>
#include <queue>
#include <algorithm>

/*
In the following description, I have left out required data structures and just assume that they exists at their first mention.

Loop through all the unvisited nodes
    perform post order DFS
        Need to check if this is visited on the recursion path or not. If it is, then just return
        Only perform DFS on the adjacent nodes which are not visited.
        Post order action is to add this node to the topological sort ordering.

If a cycle has been detected, return empty vector.
If cycle is not detected, then reverse the topological list constructed.
*/
class SolutionDfs {
public:
    auto findOrder(int numCourses, const std::vector<std::vector<int>>& prerequisites) -> std::vector<int>
    {
        // Put input in adjacency list form
        auto graph = std::vector<std::vector<int>>(numCourses);
        for(const auto& p : prerequisites)
        {
            graph[p[1]].push_back(p[0]);
        }

        auto visited = std::vector<bool>(numCourses); // so we don't run DFS on the same node twice.
        auto visitedCurrentPath = std::vector<bool>(numCourses); // detect a cycle
        auto sortedNodes = std::vector<int>{}; // to store the topological sort
        auto cycleFound = false; // if a cycle has been found, no need doing any DFS anymore.


        auto topoSort = [&](auto&& topoSort, int nodei){
            if(visited[nodei] || cycleFound)
            {
                return;
            }

            visited[nodei] = true;
            visitedCurrentPath[nodei] = true;

            for(auto adjacentNode : graph[nodei])
            {
                if(visitedCurrentPath[adjacentNode])
                {
                    cycleFound = true;
                }
                else if(!visited[adjacentNode])
                {
                    topoSort(topoSort,adjacentNode);
                }
            }
            sortedNodes.push_back(nodei);
            visitedCurrentPath[nodei] = false;
        };


        for(auto nodei = 0; nodei < numCourses; ++nodei)
        {
            if(!visited[nodei] && !cycleFound)
            {
                topoSort(topoSort,nodei);
            }
        }

        if(cycleFound) return {};

        std::ranges::reverse(sortedNodes);
        return sortedNodes;
    }
};


/*
The BFS topological sort is aka kahn's algorithm
1) Work out all th inorder
   1.2) For the nodes of inorder 0, insert it into the queue

2) BFS: while the queue is not empty
   2.1 pop from the queue and place the popped node into the result.
   2.2 for all the adjacent nodes of the popped node, decrement it's inorder.
   2.3 if the inorder of the adjacent node is 0, push it into the queue.


3) if result.size() == numCourses return result, otherwise return {}.
      
*/
class SolutionBfs {
public:
    auto findOrder(int numCourses, const std::vector<std::vector<int>>& prerequisites) -> std::vector<int>
    {
        auto graph = std::vector<std::vector<int>>(numCourses);
        auto inorder = std::vector<int>(numCourses);
        for(const auto& p : prerequisites)
        {
            graph[p[1]].push_back(p[0]);
            ++inorder[p[0]];
        }

        auto queue = std::queue<int>{};
        for(auto i = 0; i < numCourses; ++i)
        {
            if(inorder[i] == 0)
            {
                queue.push(i);
            }
        }

        auto result = std::vector<int>{};
        while(!queue.empty())
        {
            auto currentNode = queue.front();
            result.push_back(currentNode);
            queue.pop();

            for(const auto adjacentNode : graph[currentNode])
            {
                --inorder[adjacentNode];
                if(inorder[adjacentNode] == 0)
                {
                    queue.push(adjacentNode);
                }
            }
        }

        return result.size() == numCourses ? result : std::vector<int>{};
    }
};



auto main(int argc, char* argv[]) -> int
{
    return 0;
}


