/*
You are given a network of n nodes, labeled from 1 to n. 
You are also given times, a list of travel times as directed edges 
times[i] = (ui, vi, wi), 
where ui is the source node, 
      vi is the target node, and 
      wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. 

Return the minimum time it takes for all the n nodes to receive the signal. 

If it is impossible for all the n nodes to receive the signal, return -1.

##########################################################################

A signal will be sent from node k, we need to know the minimum time it takes to reach all the nodes.
This is obviously Dijstras - since the weights are non-negative.

However, we need to keep track of the maximum distance of all of the nodes, since this is the minimum time it takes to reach all the nodes.
Also, we need to check if the visited number of nodes == n, 
    this will tell us if all nodes are reached or if it's impossible, in which case we will return -1
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>

class Solution {
public:
    auto networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) -> int
    {
        // For algorithms like Dijstras, we choose the nodes from the BFS front. 
        // The BFS front consists of all the elements ADJACENT to all the nodes we have already processed.
        // Thus, we need to create an adjacency list.

        // key - source
        // value - destination and weight
        auto adj = std::unordered_map<int,std::vector<std::pair<int,int>>>{};
        for(const auto& time : times)
        {
            //src, dst, weight
            adj[time[0]].push_back({time[1],time[2]});
        }


        // Min heap, first is the weight from node k, second is the destination node.
        auto pq = std::priority_queue<
            std::pair<int,int>, 
            std::vector<std::pair<int,int>>, 
            std::greater<>>{};

        pq.push({0,k});

        auto visited = std::unordered_set<int>{};
        auto maxDistance = 0;
        while(!pq.empty())
        {
            auto [weight, node] = pq.top();
            pq.pop();

            if(visited.contains(node))
            {
                continue;
            }

            visited.insert(node);

            maxDistance = std::max(maxDistance, weight);

            if(auto it = adj.find(node); it != adj.end())
            {
                const auto& neighbours = it->second;
                for(const auto& [neigh, neighWeight] : neighbours)
                {
                    if(!visited.contains(neigh))
                    {
                        pq.push({weight + neighWeight, neigh});
                    }
                }
            }
        }

        // Impossible for all the n nodes to receive the signal
        return visited.size() == n ? maxDistance : -1;
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}

