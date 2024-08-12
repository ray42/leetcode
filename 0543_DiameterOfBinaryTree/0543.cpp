#include <algorithm>

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

              1 D=3, H=2
            /   \
  D=2, H=1 2     3 D=0, H=0
          / \ 
D=0, H=0 4   5 D=0, H=0

At each node:
Height of node = 1 + max(height(left child), height(right child))
Diameter of node = height from here going left node PLUS height from here going right node = (1+height(left child)) + (1+height(right right))

We need to return the height to feed back to the parent
We need to keep track of the max diameter.

Base case:
If a node has no children, then we return 0 as the height. The diameter can be calculated the normal way
if a node has at least 1 child, we calculate the height the normal way since we know we can go down the not null node.
   But this gives the possibility of going down a null node too! In this case, we must update our first base case to:
       if a node is null OR has no children, return 0 as the height.
*/

// Note: I've made a slight change due to neetcode's video, on how I handle the basecase and caluclating the diameter.
// But I cba to go back and correct my writing. I will correct it when I need to re-do this problem
class Solution {
public:

    using PtrTreeNode = TreeNode*;

    auto diameterOfBinaryTree(TreeNode* root) -> int
    {
        auto maxDiameter = 0;
        auto leftHeight = nodeHeight(root->left, maxDiameter);
        auto rightHeight = nodeHeight(root->right, maxDiameter);

        auto diameter = leftHeight + rightHeight;
        return std::max(maxDiameter, diameter);
    }

    auto nodeHeight(PtrTreeNode node, int& maxDiameter) -> int
    {
        if(!node)
        {
            return 0;
        }

        auto leftHeight = nodeHeight(node->left, maxDiameter);
        auto rightHeight = nodeHeight(node->right, maxDiameter);

        auto diameter = leftHeight + rightHeight;
        maxDiameter = std::max(maxDiameter, diameter);

        return 1+ std::max(leftHeight, rightHeight);
    }
};



auto main(int argc, char* argv[]) -> int
{
    // [1,2,3,4,5]
    auto p1 = new TreeNode{1};
    auto p2 = new TreeNode{2};
    auto p3 = new TreeNode{3};
    auto p4 = new TreeNode{4};
    auto p5 = new TreeNode{5};

    p1->left = p2;
    p1->right = p3;
    p2->left = p4;
    p2->right = p5;

    auto ii = Solution{}.diameterOfBinaryTree(p1);

    auto iii = 42;

    return 0;
}

