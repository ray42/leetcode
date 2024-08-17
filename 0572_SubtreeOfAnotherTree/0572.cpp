/*
Loop thorugh every node and check if it's the same tree

Edge cases:

Root  subRoot
null  null  -> is subtree of another tree
tree  null  -> is subtree of another tree - you can think of every leaf node has two of the sub trees
null  tree -> no.


*/


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
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        // Edge cases
        if(!subRoot) // handles "null  null" and "tree  null"
        {
            return true;
        }
        else if(!root) // The root is null but subRoot is not
        {
            return false;
        }
        
        // Cannot call isSameTree for left and right since we need to do it recursively, that is,
        // if we check that left is not a subtree, we need to go to the left and right subtrees of that. etc...
        return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

    auto isSameTree(TreeNode* p, TreeNode* q) -> bool
    {
        if(!p && !q)
        {
            return true;
        }
        else if (!p || !q)
        {
            return false;
        }

        return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

