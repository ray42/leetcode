
//Definition for a binary tree node.
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
    bool isSameTree(TreeNode* p, TreeNode* q) 
    {
        if(p == nullptr && q == nullptr)
        {
            return true;
        }
        // If only one of them are nullptr, we turn false
        else if(p == nullptr || q == nullptr)
        {
            return false;
        }

        // Otherwise, we know that both pointers are not null
        // So we compare the value and both left/right children

        // We need to traverse the tree!
        return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};


auto main(int argc, char* argv[]) -> int
{

    return 0;
}

