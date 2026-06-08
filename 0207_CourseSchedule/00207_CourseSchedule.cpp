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
#include <queue>

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

        // Performs a topological sort iteratively
        // stop the sort if a cycle is found and sets cycleFound = true
        auto topoSort = [&](int node) -> void
        {
            auto stack = std::stack<int>{};

            stack.push(node);

            //while(!stack.empty())
            //{
            //    auto currentNode = stack.top();
            //    stack.pop();
//
            //    for(const auto adjNode : graph[currentNode])
            //    {
            //        if(pathVisited[adjNode])
            //        {
            //            cycleFound = true;
            //            return ;
            //        }
            //    }
            //}
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


/*
kahn's algorithm:
0) If the input graph isn't in an adjacency list, put it in an adjacency list
1) Create a store of the in-orders. Also at this stage, if the in-order is 0, put it in the queue for the BFS
2) while the queue is not empty...
  2.1) pop of the queue and add this node to the topo sort list.
  2.2) For each outgoing edge from the removed node, decrement the in-degree of the destination node by 1 
  2.3) If the in-degree of a destination node becomes 0, add it to the queue.
3) If the queue is empty and there are still nodes in the graph, the graph contains a cycle and cannot be topologically sorted.
4) The nodes in the queue represent the topological ordering of the graph.

Note: We can easily check if there are still nodes in the graph by checking if the resultant topological sort has the 
      same number of nodes as the graph, if it's less, then there are still nodes on the graph.
*/
class SolutionBfsKahn {
public:
    auto canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) -> bool
    {
        // Create the adjacency list representation of the graph.
        // We can also setup the inorder!
        auto graph = std::vector<std::vector<int>>(numCourses);
        auto inorder = std::vector<int>(numCourses);
        for(const auto& p : prerequisites)
        {
            graph[p[1]].push_back(p[0]);

            // p[1] -> p[0] implies that the inorder of p0 has increased by 1.
            ++inorder[p[0]];
        }

        // Put all inorder 0 into the queue
        auto queue = std::queue<int>{};
        for(auto i = 0; i < numCourses; ++i)
        {
            if(inorder[i] == 0)
            {
                queue.push(i);
            }
        }

        auto topologicalOrdering = std::vector<int>{};
        while(!queue.empty())
        {
            const auto currentNode = queue.front();
            queue.pop();
            topologicalOrdering.push_back(currentNode);

            // Since we have "removed" the current node, we decrement all the nodes it's going into.
            // We get these by looking at it's adjacency list
            for(const auto adjacentNode : graph[currentNode])
            {
                --inorder[adjacentNode];
                if(inorder[adjacentNode] == 0)
                {
                    queue.push(adjacentNode);
                }
            }
        }

        // if a topological sort exists, then topologicalOrdering.size() == numCourses, so we return true
        return topologicalOrdering.size() == numCourses;
    }
};





auto main(int argc, char* argv[]) -> int
{
    return 0;
}

