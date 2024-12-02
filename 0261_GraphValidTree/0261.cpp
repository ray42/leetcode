
/*
Do DFS recursive, iterative
Do BFS, discuss why I cannot do iterative easily.
Do Union Find

*/


/*
A valid tree needs to have (1) no cycles and (2) it must be connected.
*/


#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>


/*
We use recursive DFS to see if there is a cycle, at the same time, we count the number of nodes.
*/
class SolutionRecursiveDfs {
public:
    auto validTree(int n, std::vector<std::vector<int>>& edges) -> bool
    {
        // If there are no edges, then it is a tree.
        if(edges.empty())
        {
            return true;
        }

        // A tree has n-1 edges, where n is the number of nodes.
        if(edges.size() != n-1)
        {
            return false;
        }
        
        // Now build the adjacency list
        // We plus 1 to the size in case the nodes start at 1 and goes to n, so the node at the 0th position won't exist
        auto graph = std::vector<std::vector<int>>(n + 1, std::vector<int>{});
        for(const auto nodes : edges)
        {
            graph[nodes[0]].push_back(nodes[1]);
            // Since this is an undirected graph, we need to go the other way too.
            graph[nodes[1]].push_back(nodes[0]);
        }

        // Do the DFS and check, return.
        auto visited = std::unordered_set<int>{};
        auto hasCycle = false;
        auto dfs = [&](auto&& dfs, int prev, int curr)
        {
            if(hasCycle)
            {
                return;
            }

            // It's important that we put this here and not just before the recursive dfs call because we need to visit all nodes, not just the children.
            // If we put this just before the recursive dfs call, then the first node we go on (node at graph[0][0]) will never be put into the visited set
            visited.insert(curr); 

            for(const auto node : graph[curr])
            {
                if(node != prev)
                {
                    if(visited.find(node) != visited.end()) // I have to use this instead of "contains" because neetcode's site does not support C++20
                    {
                        hasCycle = true;
                        return;
                    }
                    dfs(dfs,curr,node);
                }
            }
        };

        dfs(dfs,-1,edges[0][0]);

        return !hasCycle && visited.size() == n;
    }
};



class SolutionIterativeDfs {
public:
    auto validTree(int n, std::vector<std::vector<int>>& edges) -> bool
    {
        // if no edge, then it's a tree (no cycle, no disconnected node)
        if(edges.empty()) return true;

        // A tree must have n-1 edges, where n is the number of nodes
        if(edges.size() != n-1) return false;

        // Create the adjacency list
        auto adj = std::vector<std::vector<int>>(n+1,std::vector<int>{});
        for(const auto& node : edges)
        {
            adj[node[0]].push_back(node[1]);
            adj[node[1]].push_back(node[0]);
        }

        // Put the first node into the stack for iterative dfs.
        // When we pop the node, we will mark it as visited
        auto stack = std::stack<std::pair<int,int>>{}; // Node and it's previous node

        // Note: We need to keep track of the previous node, this is why we have a pair
        stack.push(std::pair<int,int>(edges[0][0],-1));
        auto visited = std::unordered_set<int>{};
        while(!stack.empty())
        {
            const auto currPrev = stack.top();
            stack.pop();
            const auto curr = currPrev.first;
            const auto prev = currPrev.second;

            if(visited.find(curr) != visited.end())
            {
                break;
            }
            visited.insert(curr);

            for(const auto& neigh : adj[curr])
            {
                if(neigh == prev)
                {
                    continue;
                }

                stack.push(std::pair<int,int>(neigh, curr));
            }
        }

        return visited.size() == n;
    }
};


class SolutionBfs {
public:
    auto validTree(int n, std::vector<std::vector<int>>& edges) -> bool
    {
        // Check no nodes and if the number of edges are n-1
        if(edges.empty()) return true;

        if(edges.size() != n-1) return false;

        // Create the adjacency list because we need to visit the neighbours of a node.
        auto adj = std::vector<std::vector<int>>(n+1,std::vector<int>{});

        for(const auto& node : edges)
        {
            adj[node[0]].push_back(node[1]);
            adj[node[1]].push_back(node[0]);
        }

        // Now get things ready and do the bfs

        // queue for bfs, need to store the node and previous node so that we do not traverse back onto ourselves
        auto queue = std::queue<std::pair<int,int>>{};
        queue.push(std::pair<int,int>(edges[0][0], -1));
        auto visited = std::unordered_set<int>{};
        while(!queue.empty())
        {
            auto currPrev = queue.front();
            queue.pop();

            auto curr = currPrev.first;
            auto prev = currPrev.second;

            // cycle found if we cannot insert
            if(auto b = visited.insert(curr); !b.second) return false;

            for(const auto neigh : adj[curr])
            {
                if(neigh == prev) continue;

                queue.push(std::pair<int,int>(neigh, curr));
            }
        }

        return visited.size() == n;
    }
};


class SolutionUnionFind {
public:

    struct UnionFind
    {
        // Index is the node, value is the parent of this node.
        std::unordered_map<int,int> parent{};

        // Used for union by rank
        // Index is the node. Value is the height of the node. The longest path from the node to a leaf. Leaf nodes have a rank of 0
        // Note that the rank may not be accurate if we implement path compression, since the path compression may or may not compress the rank of the root node.
        std::unordered_map<int,int> rank{};

        // Used for union by size - we use this to keep track of the size during a union operation. Note that only the current root nodes' sizes are accurate.
        // e.g. if we union two trees with root nodes 1 (of size 2) and root node 5 (of size 3), then in our size map, we have:
        // 1 -> 2
        // 5 -> 3
        // After the union, we will have:
        // 1 -> 5
        // 5 -> 3
        // this is because the two trees have merged with 1 being the root. But we have no need to update the 5->3 entry, since we will not use it anymore.
        // See https://takeuforward.org/data-structure/disjoint-set-union-by-rank-union-by-size-path-compression-g-46/
        std::unordered_map<int,int> size{};

        // The number of components
        int nComponents{};

        UnionFind(int n)
        {
            for(int i = 0; i < n; ++i)
            {
                // Initially, all nodes are it's own parent
                parent[i] =  i;

                // They all have height 0 (since they are all leaves)
                rank[i] = 0;

                // All have size of 1
                size[i] = 1;
            }

            nComponents = n;
        }

        auto findRoot(int node) -> int
        {
            auto p = parent[node];
            // While the parent is not it's own parent, we continuously get it's parent.
            while(p != parent[p])
            {
                // path compression - set the parent of p to be it's grand parent.
                parent[p] = parent[parent[p]];
                p = parent[p];
            }
            return p;
        }

        auto unionByRank(int n1, int n2) -> bool
        {
            auto p1 = findRoot(n1);
            auto p2 = findRoot(n2);

            // If they are the same, then we cannot merge them, so we return false.
            if(p1 == p2) return false;

            if(rank[p1] > rank[p2])
            {
                // Attach p2 to p1, no need to increase rank since p2 is smaller than p1
                parent[p2] = p1;
            }
            else if (rank[p1] < rank[p2])
            {
                // Attach p1 to p2, no need to increase rank since p1 is smaller than p2
                parent[p1] = p2;
            }
            else
            {
                // The two trees are equal size. Attach p1 to p2, increase the rank of p2 by 1
                parent[p1] = p2;
                rank[p2] +=1;
            }
            --nComponents;
            return true;
        }

        auto unionBySize(int n1, int n2) -> bool
        {
            auto p1 = findRoot(n1);
            auto p2 = findRoot(n2);

            if(p1 == p2) return false;

            // Union the smaller tree into the larger tree
            if(size[p1] < size[p2])
            {
                std::swap(p1,p2);
            }

            // p1 is now gauranteed to be equal to or greater than p2 in terms of size.
            // So we merge p2 into p1
            size[p1] += size[p2];
            parent[p2] = p1;
            --nComponents;

            return true;
        }
    };

    auto validTree(int n, std::vector<std::vector<int>>& edges) -> bool
    {
        if(edges.empty()) return true;

        if(edges.size() != n-1) return false;

        auto uf = UnionFind{n};
        for(const auto& edge : edges)
        {
            if(!uf.unionByRank(edge[0], edge[1]))
            {
                return false;
            }
        }

        return uf.nComponents == 1;
    }
};



auto main(int argc, char* argv[]) -> int
{
    //auto edges = std::vector<std::vector<int>>{{0,1},{0,2},{0,3},{1,4}};
//
    //auto iii = Solution{}.validTree(5,edges);
    //auto iiii = 42;
    return 0;
}

