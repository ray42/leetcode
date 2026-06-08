#include <vector>
#include <queue>

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
    std::vector<int> rightSideView(TreeNode* root) 
    {
        auto res = std::vector<int>{};
        auto q = std::queue<decltype(root)>{};

        if(root)
        {
            q.push(root);
        }

        while(!q.empty())
        {
            res.push_back(q.back()->val);
            const auto nnodeOnLevel = q.size();
            for(auto i = 0; i < nnodeOnLevel; ++i)
            {
                auto node = q.front();
                q.pop();

                if(node->left) q.push(node->left);
                if(node->right)q.push(node->right);
            }
        }

        return res;
    }
};

