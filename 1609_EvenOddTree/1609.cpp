
#include <queue>
#include <limits>

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
    // A binary tree is named Even-Odd if it meets the following conditions:
    // 1) The root of the binary tree is at level index 0, its children are at level index 1, their children are at level index 2, etc.
    // 2) For every even-indexed level, all nodes at the level have odd integer values in strictly increasing order (from left to right).
    // 3) For every odd-indexed level, all nodes at the level have even integer values in strictly decreasing order (from left to right).
    // Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.
    auto isEvenOddTree(TreeNode* root) -> bool
    {
        // Use BFS, for each level, we check the nodes for odd or even
        auto q = std::queue<TreeNode*>{};
        q.push(root);
        
        // Is the current level odd or even?
        auto isEven = true;
        
        while(!q.empty())
        {
            auto prevValue = isEven ? std::numeric_limits<int>::lowest() : std::numeric_limits<int>::max();

            // The number of elements in the current level
            auto nElem = q.size();

            for(auto i = 0; i < nElem; ++i)
            {
                auto node = q.front();
                q.pop();

                // If it's even then,
                // val must be odd (so return if it's even)
                // and the previous value must be smaller (so check that the previous value is equal to or greater than val)
                if(isEven && (node->val % 2 == 0 || prevValue >= node->val))
                {
                    return false;
                }
                else if(!isEven && (node->val % 2 == 1 || prevValue <= node->val))
                {
                    return false;
                }

                // Prep for the next level.
                prevValue = node->val;
                if(node->left)
                {
                    q.push(node->left);
                }
                if(node->right)
                {
                    q.push(node->right);
                }
            }
            isEven = !isEven;
        }
        return true;
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}


