/*
EASY: https://leetcode.com/problems/range-sum-of-bst/description/

RAYNOTES:

1) Brute Force: Traverse the whole BST and add only the values in range
2) Have three functions:
   leftSum - stops on the left node if value < low, calls sum on right
   sum - calls sum on both left and right
   rightSum calls sum on left and rightSum on right, rightSum will return if right value > high
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
 

class Solution 
{
public:
    auto rangeSumBST(TreeNode* root, int low, int high) -> int
    {
        if(root == nullptr) return 0;


        
        if(root->val >= low && root->val <= high)
        {
            return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        }
        else if(root->val < low)
        {
            return rangeSumBST(root->right, low, high);
        }
        else // root->val > high is the only possible option left.
        {
            return rangeSumBST(root->left, low, high);
        }
    }

private:

};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}


