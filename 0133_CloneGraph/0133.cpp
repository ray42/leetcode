



/*
My thoughts:

Let's traverse the graph in a DFS or BFS manner.

1) Since this is an undirected graph, it means if a node N1 contains node N2 in it's neighbours,
then node N2 will contain node N1 in it's neighbours. Thus, we need a way to not re-create nodes which we have
already visited. 

So we need a hash set to let us know if a node has been processed/visited or not, so we don't
process the same node twice and end up in an infinite loop.

2) Imagine that we are processing a node (so we are trying to create a deep copy of it).
Creating the node and the value is easy, but what about the adjacency list? Say N1 points to N2, N3, N4
Then in our copy, what if N2 or N3 or N4 are not created yet, what do we point to? 

We need a map of old nodes to new nodes, and we need to pre-make this prior to deep-copying the links.

3) We are already using a hash set for check if we have processed a node, and a hash map to work out the adjacency,
how can we optimise this? The current solution is:

Use DFS/BFS to traverse through the given graph to make a hash map of old nodes->new nodes.
   I can use the fact that if an old node is already in the map, I can skip it, this will stop me creating nodes twice.

Then I can just iterate through the nodes in the map and do the adjacency list in the second pass!!!!


But, can I do this in 1 pass? How about this. When performing the DFS/BFS, we assign but the value and the adjacency list.
But when doing the adjacency list, when we cannot find a node in the map of old to new olds, it means we have never
visited it before and so we must put it in the queue/stack.

Using this method, we are creating the map at the same time as generating the adjacency list, in one pass.

*/

#include <stack>
#include <vector>
#include <unordered_map>

// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }

    Node(int _val, std::vector<Node*> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};


class SolutionTwoPass {
public:

    auto cloneGraph(Node* node) -> Node*
    {
        // Pass 1: Use BFS/BFS to generate a map of old nodes to new olds
        //         Use the map to ensure that we don't create the same node twice
        // Pass 2: Loop through the elements of the map and assign the adjacency list.

        // Use iterative DFS to create a map of old nodes to new nodes.
        auto oldToNewNodes = std::unordered_map<Node*,Node*>{};
        auto stack = std::stack<Node*>{};
        if(node) 
        {
            stack.push(node);
            oldToNewNodes[node] = new Node{node->val};
        }
        
        // Pass 1
        while(!stack.empty())
        {
            auto currentNode = stack.top();
            stack.pop();

            for(auto neighbour : currentNode->neighbors)
            {
                if(!oldToNewNodes.contains(neighbour))
                {
                    stack.push(neighbour);
                    oldToNewNodes[neighbour] = new Node{neighbour->val};
                }
            }
        }

        // Pass 2:
        for(auto [oldNode, newNode] : oldToNewNodes)
        {
            for(auto oldNeighbour : oldNode->neighbors)
            {
                newNode->neighbors.push_back(oldToNewNodes[oldNeighbour]);
            }
        }

        return oldToNewNodes.empty() ? nullptr : oldToNewNodes[node];
    }
};

class SolutionOnePass {
public:

    auto cloneGraph(Node* node) -> Node*
    {
        if(!node) return nullptr;

        auto oldToNewNodes = std::unordered_map<Node*,Node*>{};
        auto stackOldNodes = std::stack<Node*>{};
               
        stackOldNodes.push(node);
        oldToNewNodes[node] = new Node{node->val};

        while(!stackOldNodes.empty())
        {
            auto currentOldNode = stackOldNodes.top();
            stackOldNodes.pop();

            for(auto neighbour : currentOldNode->neighbors)
            {
                // Make sure oldToNewNodes[neighbour] exists
                if(!oldToNewNodes.contains(neighbour))
                {
                    oldToNewNodes[neighbour] = new Node{neighbour->val};
                    // We have not seen this node before, so make sure it's in the stack for us to fill in it's adjacency list
                    stackOldNodes.push(neighbour);
                }
                oldToNewNodes[currentOldNode]->neighbors.push_back(oldToNewNodes[neighbour]);
            }
        }
        return oldToNewNodes[node];
    }
};


/*
this solution is basically the same as the above, however, we create the nodes (including the adjacency list) recursively.
We still use a map to make sure that we don't re-create nodes. That is, if a node exists in the map, we simply return it.
*/
class SolutionRecursiveDfs {
public:

    auto cloneGraph(Node* node) -> Node*
    {
        if(!node) return nullptr;

        auto oldToNewNodes = std::unordered_map<Node*, Node*>{};

        auto deepCopy = [&](auto&& deepCopy, Node* oldNode) -> Node*
        {
            if(auto it = oldToNewNodes.find(oldNode); it != oldToNewNodes.end())
            {
                return it->second;
            }

            oldToNewNodes[oldNode] = new Node{oldNode->val};

            // Also copy the adjacency list
            for(auto neigh : oldNode->neighbors)
            {
                oldToNewNodes[oldNode]->neighbors.push_back(deepCopy(deepCopy, neigh));
            }
            return oldToNewNodes[oldNode];
        };
        
        return deepCopy(deepCopy, node);
    }
};



auto main(int argc, char* argv[]) -> int
{
    return 0;
}

