
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

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

        //minMaxLeafDepth(root, 0);

        auto isBal = std::abs(maxDepth(root->left) - maxDepth(root->right)) <= 1;

        return m_maxLeafDepth - m_minLeafDepth <= 1;
    }

    int maxDepth(TreeNode* root) 
    {
        return root == nullptr ? 0 : 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

void setNull(TreeNode* node)
{
    if(!node) return;

    if(node->left && node->left->val == INT_MAX) node->left = nullptr;
    if(node->right && node->right->val == INT_MAX) node->right = nullptr;

    setNull(node->left);
    setNull(node->right);
}

// We shall use MAX_INT to denote a nullptr
auto buildTree(const std::vector<int>& vec) -> TreeNode*
{
    TreeNode * root = nullptr;
    TreeNode* current = root;

    auto queue = std::queue<TreeNode*>{};
    
    for(const auto v : vec)
    {
        if(!root)
        {
            root = new TreeNode{v};
            current = root;
            continue;
        }

        if(current->left && current->right)
        {
            current = queue.front();
            queue.pop();
        }

        if(!current->left)
        {
            current->left = new TreeNode{v};
            queue.push(current->left);
        }
        else if(!current->right)
        {
            current->right = new TreeNode{v};
            queue.push(current->right);
        }
    }

    setNull(root);

    return root;
}

auto main(int arc, char* argv[]) -> int
{
    auto root = buildTree({1,2,2,3,3,INT_MAX,INT_MAX,4,4});

    auto isBalanced = Solution{}.isBalanced(root);
    auto iii = 42;
    return 0;
}
