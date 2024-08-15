
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

/*
The definition of a height balanced tree is a tree where the height of the two sub-trees of every node
never differs by more than 1.

The depth of a node is the number of edges from the root to the node. 
The height of a node is the number of edges from the node to the deepest leaf. 
The height of a tree is a height of the root.

So the height of a tree can be calculated as the max depth of all the node.
    The maxDepth (height) of a tree can be calculated easily recursively.

Thus, the naive approach would be, for each node, we calculate the maxDepth (height) of each pair of sub-trees.
So this is O(N * 2*O(maxDepth of two subtrees) ) = O(N * 2 * N) = O(N^2)

This is very expensive! Can we do better? We can! We will only visit each node only once.

   3
 /   \
9    20
    /  \
   15   7

We can work backwards. Let's say we calculate the height of the node 7 (7 to deepest node).
We get the maximum height of the subtrees of 7 and plus 1.
At the same time, we can work out if 7 is height-balanced - we can feed these two pieces of information up.

For node 20:
Height = max height of 15 and 7 plus 1.
Is 20 balanced? Get the difference of height of 15 and 7. But if either 15 or 7 is not balanced, then we know it's not balanced from here and we can just return false.

We can do this algorithm with DFS.

I wonder, do I even need to send isBalanced back up? Must watch neetcode's video again.

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    int m_maxLeafDepth{std::numeric_limits<int>::lowest()};
    int m_minLeafDepth{std::numeric_limits<int>::max()};

    bool isBalanced(TreeNode* root)
    {
        if(!root) return true;

        auto isBal = true;

        isBalanced(root, isBal);
        return isBal;
    }

    void isBalanced(TreeNode* node, bool& balanced)
    {
        if(!balanced) return;

        if(!node) return;

        balanced = std::abs(maxDepth(node->left) - maxDepth(node->right)) <= 1;

        if(!balanced) return;

        if(node->left) isBalanced(node->left, balanced);
        if(node->right) isBalanced(node->right, balanced);
    }

    int maxDepth(TreeNode* root) 
    {
        return root == nullptr ? 0 : 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

// We shall use MAX_INT to denote a nullptr
auto buildTree(const std::vector<int>& vec) -> TreeNode*
{
    TreeNode * root = nullptr;
    TreeNode* current = root;

    auto queue = std::queue<TreeNode*>{};
    
    enum Child{
        LEFT = 0,
        RIGHT,
        NONE
    };

    auto leftRight = Child::LEFT;
    for(const auto v : vec)
    {
        if(!root)
        {
            root = new TreeNode{v};
            current = root;
            continue;
        }

        if(leftRight == Child::NONE)
        {
            current = queue.front();
            queue.pop();
            leftRight = Child::LEFT;
        }

        if(leftRight == Child::LEFT)
        {
            current->left = v == INT_MAX ? nullptr : new TreeNode{v};
            queue.push(current->left);
            leftRight = Child::RIGHT;
        }
        else if(leftRight == Child::RIGHT)
        {
            current->right = v == INT_MAX ? nullptr : new TreeNode{v};
            queue.push(current->right);
            leftRight = Child::NONE;
        }
    }

    return root;
}

auto main(int arc, char* argv[]) -> int
{
    auto root = buildTree({1,2,2,3,3,INT_MAX,INT_MAX,4,4});

    auto isBalanced = Solution{}.isBalanced(root);
    auto iii = 42;
    return 0;
}
