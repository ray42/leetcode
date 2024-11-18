/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where 

prerequisites[i] = [ai, bi] 

indicates that you must take course bi first if you want to take course ai. 
(so there is a directed edge from bi to ai).
For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.

-------------------------------------------------------------

Notes and solution:

1) We need to be careful and pay attention to the prerequisites, 
   since [[a,b]] doesn't mean b depends on a (a->b), it means, a depends on b (b->a)

2) If we can finish all courses, then a topological ordering must exist.
   If a topological ordering does not exist, it implies that there's a cycle. We need to return false in this case.

3) I shall attempt this in 3 ways:
  3.1) DFS recursive
  3.2) DFS iterative
  3.3) BFS (kahn's algorithm)

*/

#include <vector>
#include <stack>

/*
We need to create the: 
* adjacency list  - this is what the algorithm works on.
* Visited set - this tells us to not run DFS on a node which we have already ran DFS on. 
    Note: This does not check for cycles, it's to prevent scenarios like:

    A->B->\   /->D->E
           \C/
    F->G->/  \->H->I

    There are no cycles in that graph, but if we did not have the visited set, if we run DFS from A and 
    then from F, the node C and everything beyond will be visited twice.

* visitedCurrentPath - this is to detect a cycle. If a node has a path back to itself any of it's ancestors in the current DFS path, 
   then there is a cycle and we can return false straight away.
*/
class SolutionDfsRecursive {
public:
    auto canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) -> bool
    {
        auto graph = std::vector<std::vector<int>>(numCourses, std::vector<int>{});

        for(const auto& p : prerequisites)
        {
            graph[p[1]].push_back(p[0]);
        }

        auto visited = std::vector<bool>(numCourses, false);
        auto visitedCurrentPath = std::vector<bool>(numCourses, false);

        auto cycleFound = false;

        // Using recursive DFS topological sort,
        // Returns true if this graph has a cycle, false otherwise.
        auto hasCycle = [&](auto&&hasCycle, int node) -> void
        {
            if(cycleFound) return;

            visited[node] = true;
            visitedCurrentPath[node] = true;
            
            for(const auto adjNode : graph[node])
            {
                if(visitedCurrentPath[adjNode])
                {
                    // There is a cycle, return true
                    cycleFound = true;
                    return ;
                }
                else if(!visited[adjNode])
                {
                    hasCycle(hasCycle, adjNode);
                }
            }

            visitedCurrentPath[node] = false;
        };

        for(auto node = 0; node < numCourses; ++node)
        {
            if(!visited[node])
            {
                hasCycle(hasCycle, node);
                if(cycleFound)
                {
                    return false;
                }
            }
        }

        return true;
    }
};


/*
Same as the above but iterative
NOTE: To do topological sort using DFS, I need to use postorder DFS.
However, I have not learnt how to do this iteratively yet. Check out this: https://stackoverflow.com/questions/20153488/topological-sort-using-dfs-without-recursion
For now, I will skip it.
*/
class SolutionDfsIterative {
public:
    auto canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) -> bool
    {
        // Build the adjacency list
        // have a visited and pathVisited
        // Now we need a recursion stack since we want to do this iteratively.

        auto graph = std::vector<std::vector<int>>(numCourses);
        auto visited = std::vector<bool>(numCourses);
        auto pathVisited = std::vector<bool>(numCourses);

        auto cycleFound = false;

        // Performs a topologiocal sort itreratively
        // stop the sort if a cycle is found and sets cycleFound = true
        auto topoSort = [&](int node) -> void
        {
            auto stack = std::stack<int>{};

            stack.push(node);

            while(!stack.empty())
            {
                auto currentNode = stack.top();
                stack.pop();

                for(const auto adjNode : graph[currentNode])
                {
                    if(pathVisited[adjNode])
                    {
                        cycleFound = true;
                        return ;
                    }
                }
            }
        };


        for(auto node = 0; node < numCourses; ++node)
        {
            if(!visited[node])
            {
                topoSort(node);
                if(cycleFound) return false;
            }
        }

        return true;
    }
};



class SolutionBfsKahn {
public:
    auto canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) -> bool
    {
        
    }
};





auto main(int argc, char* argv[]) -> int
{
    return 0;
}

