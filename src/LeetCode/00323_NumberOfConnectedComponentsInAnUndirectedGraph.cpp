
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

/*
Count the number of connected components via dfs:

1) Maintain a visted set
2) Loop through all the nodes and perform DFS for each node unvisted node.
    Each unvisited node we come across 
*/
class SolutionRecurDfs {
public:
    auto countComponents(int n, std::vector<std::vector<int>>& edges) -> int
    {
        // n \in [0,n)
        auto adj = std::vector<std::vector<int>>(n,std::vector<int>{});

        for(const auto& e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        auto visited = std::unordered_set<int>{};
        auto dfs = [&](auto&& dfs, int node) -> void
        {
            visited.insert(node);
            for(const auto& neigh : adj[node])
            {
                if(visited.find(neigh) == visited.end())
                {
                    dfs(dfs,neigh);
                }
            }
        };
        
        auto nComponents = 0;
        for(auto node = 0; node < n; ++node)
        {
            if(visited.find(node) == visited.end())
            {
                // We have found a new connected component
                dfs(dfs,node);
                ++nComponents;
            }
        }

        return nComponents;
    }
};

class SolutionIterDfs {
public:
    auto countComponents(int n, std::vector<std::vector<int>>& edges) -> int
    {
        // Put into adjacency list form
        auto adj = std::vector<std::vector<int>>(n, std::vector<int>{});
        for(const auto& e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Maintain a visit and perform DFS on each unvisited node. Each time we come across an unvisited node, it is a new component.
        auto stack = std::stack<int>{};
        auto visited = std::unordered_set<int>{};
        auto nComponents = 0;
        
        auto dfs = [&](int node)
        {
            stack.push(node);

            while(!stack.empty())
            {
                const auto current = stack.top();
                stack.pop();
                visited.insert(current);
                for(const auto neigh : adj[current])
                {
                    if(visited.find(neigh) == visited.end())
                    {
                        stack.push(neigh);
                    }
                }
            }
        };
        for(auto node = 0; node < n; ++node)
        {
            if(visited.find(node) == visited.end())
            {
                dfs(node);
                ++nComponents;
            }
        }

        return nComponents;
    }
};

class SolutionIterBfs {
public:
    auto countComponents(int n, std::vector<std::vector<int>>& edges) -> int
    {
        // put into adjacency matrix form.
        auto adj = std::vector<std::vector<int>>(n, std::vector<int>{});
        for(const auto& e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Do the BFS and count the number of connected edges
        auto visited = std::unordered_set<int>{};
        auto queue = std::queue<int>{};
        auto bfs = [&](int node){
            queue.push(node);

            while(!queue.empty())
            {
                auto currentNode = queue.front();
                queue.pop();
                visited.insert(currentNode);

                for(const auto neigh : adj[currentNode])
                {
                    if(visited.find(neigh) == visited.end())
                    {
                        queue.push(neigh);
                    }
                }
            }
        };
        auto nComponents = 0;
        for(auto node = 0; node < n; ++node)
        {
            if(visited.find(node) == visited.end())
            {
                bfs(node);
                ++nComponents;
            }
        }

        return nComponents;
    }
};

class SolutionUnionFind {
public:

    struct UnionFind
    {

        std::unordered_map<int,int> parent{};
        std::unordered_map<int,int> rank{};
        std::unordered_map<int,int> size{};

        int nComponents;

        UnionFind(int n)
        {
            for(auto i = 0; i < n; ++i)
            {
                parent[i] = i;
                rank[i] = 0;
                size[i] = 1;
            }

            nComponents = n;
        }

        auto findRoot(int n) -> int
        {
            auto p = parent[n];
            while(p != parent[p])
            {
                // Path compression
                parent[p] = parent[parent[p]];
                p = parent[p];
            }

            return p;
        }

        auto unionByRank(int n1, int n2) -> bool
        {
            auto p1 = findRoot(n1);
            auto p2 = findRoot(n2);

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
            --nComponents;

            return true;
        }

        auto unionBySize(int n1, int n2) -> bool
        {
            auto p1 = findRoot(n1);
            auto p2 = findRoot(n2);

            if(p1 == p2) return false;

            if(p1 < p2) std::swap(p1,p2);

            parent[p2] = p1;
            size[p1] += size[p2];
            --nComponents;
            return true;
        }
    };
    auto countComponents(int n, std::vector<std::vector<int>>& edges) -> int
    {
        auto unionFind = UnionFind{n};
        for(const auto& e : edges)
        {
            unionFind.unionBySize(e[0], e[1]);
        }

        return unionFind.nComponents;
    }
};




auto main(int argc, char* argv[]) -> int
{
    auto n=3;
    auto edges= std::vector<std::vector<int>>{{0,1},{0,2}};
    auto iii = SolutionUnionFind{}.countComponents(n,edges);
    std::cout << "Hello" << iii << '\n';
    return 0;
}



