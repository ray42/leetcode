#pragma once
#include "common_types.hpp"
#include <limits>
#include <algorithm>


class Solution1448 {
public:
    int goodNodes(TreeNode* root) 
    {
        return numGoodNodes(root, std::numeric_limits<int>::lowest());
    }

    auto numGoodNodes(TreeNode* node, int greatestNodeVal) -> int
    {
        if(!node)
        {
            return 0;
        }

        auto x = node->val >= greatestNodeVal ? 1 : 0;
        auto y = std::max(node->val, greatestNodeVal);
        
        return x + numGoodNodes(node->left, y) + numGoodNodes(node->right, y);
    }
};

/*
auto main(int argc, char* argv[]) -> int
{
    return 0;
}
*/
