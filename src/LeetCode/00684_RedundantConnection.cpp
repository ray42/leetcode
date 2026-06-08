/*
Problem: 
In this problem, a tree is an undirected graph that is connected and has no cycles.
You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. 
The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. 

The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. 
***If there are multiple answers, return the answer that occurs last in the input.***

############################################

Solution

Finding a redundant connection is the same finding a cycle in a loop and then returning the edge which forms the cycle.

We can do this with:
1) Recursive DFS
2) Iterative DFS
3) Iterative BFS
4) Union Find

However, note the last contraint:

***If there are multiple answers, return the answer that occurs last in the input.***

if we put the edges into an adjacency list, then we loop over the nodes in order (from 0 to n-1), there is no guarantee that the 
edge we detect to complete a cycle will be the node which appears last in the list.

I can try to put all the edges which forms a cycle in a set and then check which ones of these edges comes first in the list.
    However, this seems too hard - how do we find all the edges which forms a cycle?!

So we know that we need to respect the order 

Very un-optimal solution: We can create many adjacency matrices, by added one edge at a time.
Each time we add an edge, we check if adding this edge makes a cycle, if it does form a cycle, then we know that
it must be the last edge in the list which forms a cycle, since the graph started of as a tree and one edge is added, thus, there can only be one cycle.

Time: O(E * (V + E)), E = edges, V = vertices. Since the DFS is E+V and we need to do it E times (since we need to do a DFS each time we add an edge).
Space: O(V + E) - The adjacency list is a list of a list. The other list is V long and the number of entries in all the inner list is E 

E.g.
[
1: [2,3,4]
2: [1,3]
3: [1]
4: [1]
]

##########################################################################################

Actual solution: We need a way to loop through the edges list and do something with each of them to see which one will form a cycle.
This is exactly what Union Find is meant to do!

Time: O ( V + (E * \alpha (V)) ) - V is for initialising the Union Find. E*\alpha (V) is for calling the "union" function E times, 
        each time union is called, "findRoot" is called, which is amortised to \alpha (V) -> O(1)
Space: O( V )

*/


#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>


class SolutionUnionFind {
public:

    struct UnionFind
    {
        std::unordered_map<int,int> parent{};
        std::unordered_map<int,int> rank{};
        std::unordered_map<int,int> size{};

        UnionFind(const std::vector<std::vector<int>>& edges)
        {
            for(const auto& e : edges)
            {
                parent[e[0]] = e[0];
                parent[e[1]] = e[1];

                rank[e[0]] = 0;
                rank[e[1]] = 0;

                size[e[0]] = 1;
                size[e[1]] = 1;
            }
        }

        auto findRoot(int n) -> int
        {
            auto p = parent[n];
            while(p != parent[p])
            {
                // path compression
                parent[p] = parent[parent[p]];
                p = parent[p];
            }

            return p;
        }

        auto unionByRank(int n1, int n2) -> bool
        {
            const auto p1 = findRoot(n1);
            const auto p2 = findRoot(n2);

            if(p1 == p2) return false;

            if(rank[p1] < rank[p2])
            {
                parent[p1] = p2;
            }
            else if(rank[p1] > rank[p2])
            {
                parent[p2] = p1;
            }
            else
            {
                parent[p2] = p1;
                ++rank[p1];
            }

            return true;
        }

        auto unionBySize(int n1, int n2) -> bool
        {
            auto p1 = findRoot(n1);
            auto p2 = findRoot(n2);

            if(p1 == p2) return false;

            if(size[p1] < size[p2]) std::swap(p1,p2);

            // p1 always has the equal to or bigger rank.

            parent[p2] = p1;
            size[p1] += size[p2];

            return true;
        }
    };

    auto findRedundantConnection(std::vector<std::vector<int>>& edges) -> std::vector<int>
    {
        auto uf = UnionFind(edges); 
        for(const auto& e : edges)
        {
            if(!uf.unionByRank(e[0],e[1]))
            {
                return {e[0],e[1]};
            }
        }

        return {};
    }
};