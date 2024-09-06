/*
This is very similar to "543, Diameter of Binary Tree", but instead we get the value instead of the diameter.

*** Thought Process ***
What so we need to find? The "maximum path sum of ANY non-empty path"
The path sum of a path is the sum of the node's values in the path

So at each node, if we can calculate the maximum path sum through the node, we can track the maximum of these maximums.
Note that, we can have multiple path sums through a node. E.g.

      1
    /   \
   2     3
  / \   / \
 4   5 6   7

There are multiple paths going through 1, and it doesn't even need to include the roots.
So how to find the max path sum going through a node?

Easy, it will be the value of this node PLUS the max value from the left and max value from the right.
What is the max value from the left/right? it'll be the sum from the leaf to this left/right node.
If the max sum from left/right happens to be negative, then we don't include it (we treat the max left/right value as 0).

Remember that we need to return the max value from leaf to here, so that the parent node can calculate it's
1) max path sum through it's node
2) max value from a root to it's node or 0, which ever is greater.

OK, let's code this up! The below "just a thought" is about large negative numbers which I have covered here.

------------------------------------------------------
I JUST HAD A THOUGHT:
I just had a thought... if we see a big negative number, e.g.

      1
    /   \
   2     3
  / \   / \
 4  5 -100 -200
            \
             8
then we won't want to include the path -200 to 8 in our paths, we can do better if we ignore it.
So what I mean is, if we are at 3, and we want to pass up to node 1 "what is the largest path sum formed when including node 3",
then we don't want to include -100 or -200 in that calculation. so we want something like

return max(this->val, this->val + maxPath(left), this->val + maxPath(right)).

This is an edge case.

Other edge cases: What if we have 1 node? In my mind, this shouldn't form a path and so the answer should be 0. 
But leetcode seems to think 1 node can form a path.

-------------------------------------------------------

*/

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

  int maxPathSum(TreeNode* root)
  {
    auto maxPathSumOfAllNodes = INT_MIN;
    return maxValueFromLeaf(root, maxPathSumOfAllNodes);
  }

  int maxValueFromLeaf(TreeNode* root, int& maxPathSumOfAllNodes)
  {
    if(!root)
     return 0;

    auto maxLeft = std::max(0,maxValueFromLeaf(root->left,maxPathSumOfAllNodes));
    auto maxRight = std::max(0,maxValueFromLeaf(root->right,maxPathSumOfAllNodes));

    // Work out the max path sum passing through this node and update maxPathSumOfAllNodes
    auto thisMaxPathSum = std::max(0, maxLeft + root->val + maxRight);
    maxPathSumOfAllNodes = std::max(thisMaxPathSum, maxPathSumOfAllNodes);

    // Return the max value from leaf to this node or 0, which ever is greater.
    return std::max(0, root->val + std::max(maxLeft, maxRight));
  }

};



