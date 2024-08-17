




// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class SolutionRecursion {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if(!root) return root;

        if(p->val > q->val)
        {
            auto tmp = p;
            p = q;
            q = tmp;
        }

        if((p->val <= root->val && q->val > root->val) || (p->val < root->val && q->val >= root->val))
        {
            return root;
        }
        else if(p->val < root->val && q->val < root->val)
        {
            return lowestCommonAncestor(root->left, p, q);
        }
        else if(p->val > root->val && q->val > root->val)
        {
            return lowestCommonAncestor(root->right, p, q);
        }

        return nullptr;
    }
};

/*
This is quite neat.
if p&q < root, we look left.
if p&q > root, we look right.

If it's none of the above, then it must be that p and q are in separate sub trees:

  root
  /  \
p     q

or, p or q are on the root:
  q
 /
p

In either case, the LCA is the current node we are on.

Also, we don't need to call recursively, we can just keep track of the current node.
*/
class SolutionIter {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        auto curr = root;

        while(curr)
        {
            if(p->val < curr->val && q->val < curr->val)
            {
                curr = curr->left;
            }
            else if(p->val > curr->val && q->val > curr->val)
            {
                curr = curr->right;
            }
            else
            {
                return curr;
            }
        }

    }
};

