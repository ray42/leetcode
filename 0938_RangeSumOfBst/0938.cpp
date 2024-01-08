/*
EASY: https://leetcode.com/problems/range-sum-of-bst/description/

Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].

Example 1:

Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
Output: 32
Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.

Example 2:

Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
Output: 23
Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.

Constraints:

    The number of nodes in the tree is in the range [1, 2 * 104].
    1 <= Node.val <= 105
    1 <= low <= high <= 105
    All Node.val are unique.

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


