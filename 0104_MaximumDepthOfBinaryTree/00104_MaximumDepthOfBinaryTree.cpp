#include <algorithm>
#include <queue>
#include <stack>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
NOTE: THE DEFINITION OF DEPTH USED IN THIS PROBLEM IS INCORRECT.
THEY DEPTH IS THE NUMBER OF EDGES FROM A NODE TO THE ROOT. THEY ARE COUNTING NODES IN THIS PROBLEM INSTEAD.
BAD LEETCODE! BAD

This is my preferred solution.

The depth of a node is the number of edges from the root to the node. 
The height of a node is the number of edges from the node to the deepest leaf. 
    The height of a tree is a height of the root.

Note: This problem is called "Maximum Depth of Binary Tree".
      Depth of a node is the number of edged from root to the node.
      The maximum depth is the same as the height of the tree. In this solution, we are calculating the height at each node,
      eventually, we calculate the height of the root node :)
*/
class SolutionRecrusiveDFS {
public:
    int maxDepth(TreeNode* root) 
    {
        return root == nullptr ? 0 : 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

// Each time we visit a node, we push it to a container, then we want to visit the other nodes, not the one we just push.
// This means we use a queue. Also, how do we track the depth? By counting the levels, since this is a LEVER ORDER TRAVERSAL.
class SolutionIterativeBfs {
public:

    using PtrTreeNode = TreeNode*;

    int maxDepth(TreeNode* root) 
    {
        auto queue = std::queue<PtrTreeNode>{};
        
        if(root) queue.push(root);

        auto level = 0;
        while(!queue.empty())
        {
            // We are on a level now
            ++level;

            // Loop through all the nodes on this level.
            const auto nNodesInLevel = std::ssize(queue);
            for(auto i = decltype(nNodesInLevel){}; i < nNodesInLevel; ++i)
            {
                const auto node = queue.front();
                if(node->left) queue.push(node->left);
                if(node->right) queue.push(node->right);
                queue.pop();
            }
        }

        return level;
    }
};

// Recall in DFS, we visit the children of a node before we visit the siblings of the node.
// So we have a stack, we pop a node and insert all it's children. 
// When we pop again, we are visiting the children of the node we just popped. 
// Note that we cannot feed the dept of the children back to the parent since it was visited in a previous iteration and not stored anywhere.
// So how do we actually maximum depth?
// 
// When we push a node into the stack, we can also insert the dept (distance to the root).
// Then we keep track of the max. This is actually more true to the name of the problem (max depth)
// than the recursive DFS version where we calculate the height of each node and then return the height of the root.
class SolutionIterativeDfs {
public:

    using PtrTreeNode = TreeNode*;

    struct NodeDepth
    {
        PtrTreeNode node{nullptr};
        int depth{0};
    };

    int maxDepth(TreeNode* root) 
    {
        auto stack = std::stack<NodeDepth>{};

        auto resMaxDepth = 0;

        if(root) stack.push({root, 1});

        while(!stack.empty())
        {
            auto [node, depth] = stack.top();
            resMaxDepth = std::max(resMaxDepth, depth);
            stack.pop();
            if(node->left) stack.push({node->left, depth+1});
            if(node->right) stack.push({node->right, depth+1});
        }

        return resMaxDepth;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

