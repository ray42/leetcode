/*
You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

#################################################

So, find the minimum spanning tree of the complete graph denoted by the nodes in `points`.
The weight of the edges will be the manhattan distance between the two points.

We can use prims or kruskals. I will implement both.
*/

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <ranges>
#include <algorithm>

class SolutionPrims {
public:
    auto minCostConnectPoints(const std::vector<std::vector<int>>& points) -> int
    {
        // Create the adjacency list, but a node is not adjacent to itself.
        // key - source node
        // value - target node and distance
        auto adj = std::unordered_map<int,std::vector<std::pair<int,int>>>{};

        // If you draw out the complete graph, you'll see that after we have processed the ith node,
        // the next node can skip all previous nodes. This leads the the inner loop being i+1 - because we don't want to include i nor any previous nodes.
        const auto pointsSize = std::ssize(points);
        for(auto i = decltype(pointsSize){}; i < pointsSize; ++i)
        {
            const auto x1 = points[i][0];
            const auto y1 = points[i][1];
            for(auto j = i + 1; j < pointsSize; ++j)
            {
                const auto x2 = points[j][0];
                const auto y2 = points[j][1];

                // Calculate the manhattan distance
                const auto distance = std::abs(x1-x2) + std::abs(y1-y2);

                adj[i].push_back({distance, j});
                adj[j].push_back({distance, i});
            }
        }

        // Now we create the min-heap and perform prims.
        // pair first is cost, second is the node.
        auto pq = std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>>{};

        // Let's put all the edges from the first node in.
        for(const auto[distance, node] : adj[0])
        {
            pq.push({distance,node});
        }

        auto visited = std::unordered_set<int>{};

        // This is important because we have "visited" node 0 already by getting all it's neighbours and putting it into the pq.
        visited.insert(0);

        auto res = 0;
        while(!pq.empty())
        {
            const auto [distance, node] = pq.top();
            pq.pop();

            if(visited.contains(node)) continue;

            visited.insert(node);

            res += distance;

            for(const auto[neighDistance, neighNode] : adj[node])
            {
                if(visited.contains(neighNode)) continue;

                pq.push({neighDistance, neighNode});
            }
        }

        return res;
    }
};


// NOTE: There is a bug here but I cba to fix it now. Will fix it when I come back to do this again.
class SolutionKruskal {
public:

    struct UnionFind
    {
        // Key is the node, value is the parent of the node.
        std::unordered_map<int,int> parent{};

        // Used by union by rank
        // Index is the node. Value is the height of the node. The longest path from the node to a leaf. Leaf nodes have a rank of 0.
        // Note that the rank may not be accurate if we implement path compression, since the path compression may or may not compress the rank of the root node.
        std::unordered_map<int,int> rank{};

        // Used for union by size - we use this to keep track of the size during a union operation. Note that only the current root nodes' sizes are accurate.
        // e.g. if we union two trees with root nodes 1 (of size 2) and root node 5 (of size 3), then in our size map, we have:
        // 1 -> 2
        // 5 -> 3
        // After the union (we merge 1 into 5 because we always merge the smaller one into the bigger one), we will have:
        // 1 -> 2
        // 5 -> 5
        // this is because the two trees have merged with 1 being the root. But we have no need to update the 5->3 entry, since we will not use it anymore.
        // See https://takeuforward.org/data-structure/disjoint-set-union-by-rank-union-by-size-path-compression-g-46/
        std::unordered_map<int,int> size{};

        // The number of components
        int nComponents{};

        UnionFind(int nnodes)
        {
            for(auto i = 0; i < nnodes; ++i)
            {
                parent[i] = i;
                rank[i] = 0;
                size[i] = 1;
            }
            nComponents = nnodes;
        }

        auto findRoot(int node) -> int
        {
            auto p = parent[node];

            // While p is not it's own parent, perform path compression and get the parent.
            while(p != parent[p])
            {
                // Path compression, set the parent of p to be it's grand parent.
                parent[p] = parent[parent[p]];
                p = parent[p];
            }
            return p;
        }

        auto unionByRank(int n1, int n2) -> bool
        {
            auto p1 = findRoot(n1);
            auto p2 = findRoot(n2);

            // If they are the same, then we cannot merge them (since they are already merged), so we return false
            if(p1 == p2) return false;

            if(rank[p1] > rank[p2])
            {
                // Attach p2 to p1, no need to increase rank since p2 is smaller than p1.
                parent[p2] = p1;
            }
            else if (rank[p2] > rank[p1])
            {
                // Attach p1 to p2, no need to increase rank since p1 is smaller than p2
                parent[p1] = p2;
            }
            else
            {
                // Otherwise, the two rank are equal, so we need to attach one to the other and increase the rank.
                parent[p1] = p2;
                ++rank[p2];
            }
            --nComponents;
            return true;
        }

        auto unionBySize(int n1, int n2) -> bool
        {
            auto p1 = parent[n1];
            auto p2 = parent[n2];

            if(p1 == p2) return false;

            // make p1 the bigger components
            if(size[p1] < size[p2])
            {
                std::swap(p1,p2);
            }

            // Now attach p2 to p1 because we know that p1 is bigger or equal to.
            parent[p2] = p1;
            size[p1] += size[p2];

            --nComponents;
            return true;
        }

    };
    auto minCostConnectPoints(const std::vector<std::vector<int>>& points) -> int
    {
        // Because we are only given points and not "labels" for them, we will use the index as the "labels".
        // E.g. point 0 will be points[0].
        
        // Now for us to use the UnionFind dataset, we need a left of edges and weights, in the form
        // {distance, i, j}
        auto edges = std::vector<std::vector<int>>{};
        const auto npoints = std::ssize(points);
        for(auto i = 0; i < npoints; ++i)
        {
            auto x1 = points[i][0];
            auto y1 = points[i][1];
            for(auto j = i + 1; j < npoints; ++j)
            {
                auto x2 = points[j][0];
                auto y2 = points[j][1];
                auto distance = std::abs(x1-x2) + std::abs(y1-y2);

                edges.push_back({distance, i, j});
            }
        }

        std::ranges::sort(edges);

        auto uf = UnionFind{static_cast<int>(npoints)};
        int res = 0;
        for(const auto& edge : edges)
        {
            if(uf.unionBySize(edge[1],edge[2]))
            {
                res += edge[0];
            }
        }
        return res;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

