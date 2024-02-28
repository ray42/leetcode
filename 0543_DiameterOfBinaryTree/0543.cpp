

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
    auto diameterOfBinaryTree(TreeNode* root) -> int
    {
        // The diameter of the node can be calculated as the depth of the left tree plus the depth of the right tree.
        // What we want to do is to work out the longest diameter of all the nodes.


        
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}

