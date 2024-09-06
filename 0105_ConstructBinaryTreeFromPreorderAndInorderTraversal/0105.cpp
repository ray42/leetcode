/*
Look at both Neetcode's video and https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solutions/5632202/video-2-solutions-with-o-n-2-and-o-n-time/
I shall try to explain all solutions here.

From NeetCode:

Let's say we have:
    1
   / \
  2   3
 / \ / \
4  5 6  7

What's the pre-order and post order?
Preorder: print this node first, then do the same to the left and right subtree
Inorder: Print the left subtree, then this node, then the right subtree.
Pre: 1 2 4 5 3 6 7
in:  4 2 5 1 6 3 7

We know that the first node must be the first element in the pre-list.
Then what? Let's locate this element in the in list:
Pre: [1] 2 4  5  3 6 7
in:   4  2 5 [1] 6 3 7

What does this tell us? Well, since in the in list, we visit the node we are at in between the left and right, 
so locating the root node in the pre-list partitions the nodes in which are in the left/right subtrees.
We know that there are 3 elements in the left subtree and 3 in the right.
Using this information, we can further partition the pre-list:
pre:     [2 4  5]  [3 6 7]
          left      right
in:      [4  2 5]  [6 3 7]
Now we can apply the algorithm again to the left and right.

------

So what needs to happen at each recursive step?
(this step requires deep thought and maybe trial and error)

We know what we finally need to return the root node.

We create the root node from the preorder. If this is empty, we return a nullptr.

If it's not empty, then we need to partition the two preorder and inorder lists and make two recursive calls for the left and right node.
The recursive calls will return their root nodes which we can attach to the root node in the current function.

---------------------------

NOTE: I really need to read the solution on leetcode for the O(N) solution when I revisit this.
Neetcode's code is very similar to mine, but with better iterator manipulation
*/

#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// First attempt, using copy of vectors. I shall optimise it later on.
class Solution {
public:
    TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder)
    {
        if(preorder.empty()) return nullptr;


        // There is at least 1 node, we shall create it, then partition the two arrays
        const auto& rootVal = preorder.front();
        auto root = new TreeNode{rootVal};

        // Locate the rootVal in inorder to create the two new inorder vectors
        auto leftInorder = std::vector<int>{};
        auto rightInorder = std::vector<int>{};
        auto doLeft = true;
        for(const auto v : inorder)
        {
            if(v == rootVal)
            {
                doLeft = false;
            }
            else if(doLeft)
            {
                leftInorder.push_back(v);
            }
            else
            {
                rightInorder.push_back(v);
            }
        }

        
        auto leftPreorder = std::vector<int>{preorder.begin() + 1, preorder.begin() + 1 + leftInorder.size()};
        auto rightPreorder = std::vector<int>{preorder.begin() + 1 + leftInorder.size(), preorder.begin() + 1 + leftInorder.size() + rightInorder.size()};
        

        root->left = buildTree(leftPreorder, leftInorder);
        root->right = buildTree(rightPreorder, rightInorder);
        return root;

    }
};

auto main()->int
{
    auto s = Solution{}.buildTree({1, 2, 4, 5, 3, 6, 7},{4, 2, 5, 1, 6, 3, 7});
    return 0;
}

