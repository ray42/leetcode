


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
    int kthSmallest(TreeNode* root, int k)
    {
        auto i = int{};
        auto res = int{};
        dfs(root, k, i, res);
    }

    auto dfs(TreeNode* node, const int& k, int& i, int& res) -> void
    {
        if(!node || k == i)
        {
            return;
        }

        dfs(node->left, k, i, res);

        ++i;
        if(k == i)
        {
            res = node->val;
            return ;
        }
        dfs(node->right, k, i, res);
    }
};
