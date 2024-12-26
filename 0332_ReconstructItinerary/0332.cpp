

#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

/*
This is about finding the Eulerian Path - a path which crosses every path once. See my notes on Obsidian.
*/


/*
The Naive approach is to perform DFS and add each node to the solution as we come across them (preorder DFS).
Now, because this is a naive method, we need to backtrack if the answer we have is invalid (because the number of edges don't match)

NOTE: I'm pretty sure that this works, but I get timelimit exceeded.
So, I'll just go straight to the optimised algorithm
*/
class SolutionPreorderRecursiveDfs {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
    {
        // Since DFS requires visiting neighbours, we will need to put tickets into adjacency lists.

        // Sorting so that when we create the adjacency list, the lexicographically smaller one comes first
        std::ranges::sort(tickets);

        auto adj = std::unordered_map<std::string,std::vector<std::string>>{};
        for(const auto ticket : tickets)
        {
            adj[ticket[0]].push_back(ticket[1]);
        }

        auto res = std::vector<std::string>{};

        const auto numEdgesPlus1 = tickets.size() + 1;

        auto dfs = [&](auto&& dfs, std::string_view currentEdge){

            if(res.size() == numEdgesPlus1)
            {
                return true;
            }

            // If the adjacency list doesn'
            if(!adj.contains(currentEdge.data()))
            {
                return false;
            }

            // Because we are going go modify adj, we take a copy to loop through
            auto tempNeighs = adj[currentEdge.data()];
            //for(const auto neigh : tempNeighs)
            for(auto i = 0; i < tempNeighs.size(); ++i)
            {
                const auto s = tempNeighs[i];
                // I'm using empty string as a sentinel instead of continuously removing and adding to the vector
                if(s == "") continue;

                res.push_back(tempNeighs[i]);

                adj[currentEdge.data()][i] = "";

                if(dfs(dfs,s)) return true;

                // backtrack
                adj[currentEdge.data()][i] = s;
                res.pop_back();
            }


            return false;
        };
        
        res.push_back("JFK");

        // Now we need to perform the dfs
        dfs(dfs, "JFK");

        return res;
    }
};



class SolutionPreorderIterativeDfs {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
    {

    }
};


/*
// Hierholzer's algorithm

It's the post-order version of the above.
In other words, during the DFS, at each node, we make sure that we go through all the edges coming out of this node before we put this node

This ensures that we've traveled through all the edges after this node, including any loops and the end node. 

In particular, let's say we have:
    C
    ||
A-> B ->D

say we are at node B, then we can take two edges: to C and to D.

It doesn't matter which edge the DFS algorithm takes because the DFS algorithm will only stop at the end node 
(since it will not have anymore edges coming out of it if we keep deleting edges as we go out). What do I mean?

Say we have a node with two in edges and one out edge:
---> A --->
--->

Let's take an edge into A, then the only thing to do is to take the other edge out of it, let's delete the two edges:
---> A 

So we have one more edge into A left. Eventually, we will take this edge and the DFS cannot continue and we add this node to the solution.

Back to the example, we are currently at B, and we will eventually end up at the stop node D. There does not matter how many non-terminal nodes
in between B and D, since these are non-terminal nodes, there will be an in and out edge and we can go in and out of.

This is why forcing every edge to be taken from the node before putting the node into the solution works.

However, we must remember to reverse the solution since we are adding the stop node first (since this is a post-order DFS)

Note: This is VERY similar to DFS topological sort (see LC 210 Course Schedule II) since we also perform a post-order DFS and have to reverse the solution afterwards.
The difference there is that, the DFS only goes to the nodes which we haven't visit. Here, he's OK to visit a node multiple times,
in fact, we must if there are multiple in and out edges - all that matters here is that we must visit every edge.

See my notes in obsidian.

*/
class SolutionPostorderRecursiveDfs {
public:
    auto findItinerary(std::vector<std::vector<std::string>>& tickets) -> std::vector<std::string>
    {
        // Need to visit the smaller nodes first, so let's sort tickets, so that when we construct the adjacency list,
        // each adjacency list is in lexicographical order.
        // Then in the DFS, we must make sure that we visit the lexicographical smaller nodes first (but visiting from the front of the vector)

        std::ranges::sort(tickets);

        auto adj = std::unordered_map<std::string,std::vector<std::string>>{};
        for(const auto& ticket : tickets)
        {
            adj[ticket[0]].push_back(ticket[1]);
        }

        auto res = std::vector<std::string>{};

        auto dfs = [&](auto& dfs, std::string_view currentNode) -> void
        {
            auto& neighbours = adj[currentNode.data()]; 
            const auto numNeighs = neighbours.size();
            for(auto i = 0; i < numNeighs; ++i)
            {
                if(neighbours[i] == "") continue;

                auto currentNeigh = neighbours[i];
                neighbours[i] = "";

                dfs(dfs,currentNeigh.data());
            }
            res.push_back(currentNode.data());
        };
        dfs(dfs,"JFK");
        std::ranges::reverse(res);
        return res;
    }
};


// Hierholzer's algorithm
class SolutionPostorderIterativeDfs {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
    {

    }
};


auto main(int argc, char* argv[]) -> int
{
    //auto edges = std::vector<std::vector<std::string>>
    //{
    //    {"A", "B"},
    //    {"A", "C"},
    //    {"C", "A"},
    //};

    auto edges = std::vector<std::vector<std::string>>
    {
        {"A", "B"},
        {"A", "C"},
        {"B", "A"},
    };

    //auto sol = Solution{}.findItinerary(edges);

    return 0;
}


