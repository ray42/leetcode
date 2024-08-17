
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
    auto levelOrder(TreeNode* root) -> std::vector<std::vector<int>>
    {
        auto vecLevelOrder = std::vector<std::vector<int>>{};

        auto queue = std::queue<TreeNode*>{};

        if(root)
        {
            queue.push(root);
        }

        while(!queue.empty())
        {
            // prepare to loop through nodes on this level
            auto nnodesOnLevel = queue.size();
            vecLevelOrder.push_back(std::vector<int>{});
            for(auto i = 0; i < nnodesOnLevel; ++i)
            {
                auto node = queue.front();
                queue.pop();

                vecLevelOrder.back().push_back(node->val);
                if(node->left) queue.push(node->left);
                if(node->right) queue.push(node->right);
            }
        }

        return vecLevelOrder;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
