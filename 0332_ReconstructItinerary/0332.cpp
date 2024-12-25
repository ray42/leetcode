

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

This ensures that we've traveled through all the edges after this node, including any loops and the end node. See my notes in obsidian.
However, this means that 
*/

class SolutionPostorderRecursiveDfs {
public:
    auto findItinerary(std::vector<std::vector<std::string>>& tickets) -> std::vector<std::string>
    {

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


