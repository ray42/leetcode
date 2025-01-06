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


class SolutionKruskal {
public:
    auto minCostConnectPoints(const std::vector<std::vector<int>>& points) -> int
    {
        
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

