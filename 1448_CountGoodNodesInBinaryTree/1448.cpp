#include <limits>
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

class Solution {
public:
    int goodNodes(TreeNode* root) 
    {
        return numGoodNodes(root, std::numeric_limits<int>::lowest());
    }

    auto numGoodNodes(TreeNode* node, int greatestNodeVal) -> int
    {
        if(!node)
        {
            return 0;
        }

        auto x = node->val >= greatestNodeVal ? 1 : 0;
        auto y = std::max(node->val, greatestNodeVal);
        
        return x + numGoodNodes(node->left, y) + numGoodNodes(node->right, y);
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
