#include <queue>

// Definition for a binary tree node.
struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
// OKay, so this didn't work because we get an overflow due to the 2*
//class Solution {
//public:
//    auto findBottomLeftValue(TreeNode* root) -> int
//    {
//        if(!root)
//        {
//            return 0;
//        }
//
//        auto mostDepth = 0;
//        auto smallestIndex = 0;
//        auto value = root->val;
//
//        findBottomLeftValue(root->left, 1, 1, value, mostDepth, smallestIndex);
//        findBottomLeftValue(root->right, 1, 2, value, mostDepth, smallestIndex);
//        
//        return value;
//    }
//
//private:
//
//    auto findBottomLeftValue(TreeNode* node, int depth, int index, int& value, int& mostDepth, int& smallestIndex) -> void
//    {
//        if(!node)
//        {
//            return;
//        }
//
//        // Calculate the new depth and index.
//        if((depth > mostDepth) || (depth == mostDepth && index < smallestIndex))
//        {
//            mostDepth = depth;
//            smallestIndex = index;
//            value = node->val;
//        }
//
//        findBottomLeftValue(node->left, depth + 1, 2* index+1, value, mostDepth, smallestIndex);
//        findBottomLeftValue(node->right, depth + 1, 2* index+2, value, mostDepth, smallestIndex);
//    }
//};


class Solution {
public:
    
    // We travel the tree level by level from right to left.
    // This means that the last value of the traversal is the most bottom left.
    int findBottomLeftValue(TreeNode* root) 
    {
        if(!root)
        {
            return 0;
        }

        auto q = std::queue<TreeNode*>{};
        q.push(root);
        auto bottomLeftValue = int{};

        while(!q.empty())
        {
            auto node = q.front();
            q.pop();

            bottomLeftValue = node->val;

            // This is the key, to travel from right to left, we insert the right child first.
            if(node->right)
            {
                q.push(node->right);
            }
            if(node->left)
            {
                q.push(node->left);
            }

        }

        return bottomLeftValue;
    }
};


class Solution2 {
public:
    int findBottomLeftValue(TreeNode* root) {
        std::queue<TreeNode*> q;
        q.push(root);
        int leftmost_value;

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            leftmost_value = node->val;

            if (node->right) {
                q.push(node->right);
            }
            if (node->left) {
                q.push(node->left);
            }
        }

        return leftmost_value;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto n0 = TreeNode{2};
    auto n1 = TreeNode{1};
    auto n2 = TreeNode{3};
    n0.left = &n1;
    n0.right = &n2;

    auto ss = Solution{}.findBottomLeftValue(&n0);
    return 0;
}
