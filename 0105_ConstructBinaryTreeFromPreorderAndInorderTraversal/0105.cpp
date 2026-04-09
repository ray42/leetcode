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
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

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


vector<int> postorderIterativeOneStack(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  TreeNode* curr = root;
  TreeNode* lastVisited = nullptr;

  while (curr != nullptr || !st.empty()) {
    // Go as far left as possible
    while (curr != nullptr) {
      st.push(curr);
      curr = curr->left;
    }

    TreeNode* node = st.top();

    // If right child exists and hasn't been visited yet,
    // move to the right subtree
    if (node->right != nullptr && lastVisited != node->right) {
      curr = node->right;
    } else {
      // Otherwise, visit the node
      result.push_back(node->val);
      lastVisited = node;
      st.pop();
    }
  }

  return result;
}

auto main()->int
{
    //auto s = Solution{}.buildTree({1, 2, 4, 5, 3, 6, 7},{4, 2, 5, 1, 6, 3, 7});


//        1
//       / \
//      2   3
//     / \   \
//    4   5   6

//  Traversal results:
// - **Preorder (Root, Left, Right)** -> `1 2 4 5 3 6`
// - **Inorder (Left, Root, Right)** -> `4 2 5 1 3 6`
// - **Postorder (Left, Right, Root)** -> `4 5 2 6 3 1`
// - **Level Order** -> `1 2 3 4 5 6`

    auto tn1 = TreeNode{1};
    auto tn2 = TreeNode{2};
    auto tn3 = TreeNode{3};
    auto tn4 = TreeNode{4};
    auto tn5 = TreeNode{5};
    auto tn6 = TreeNode{6};

    tn1.left = &tn2;
    tn1.right = &tn3;
    tn2.left = &tn4;
    tn2.right = &tn5;
    tn3.right = &tn6;

    auto postorder = postorderIterativeOneStack(&tn1);
    for(const auto v : postorder)    {
        std::cout << v << " ";
    }
    std::cout << std::endl;


    


    return 0;
}

