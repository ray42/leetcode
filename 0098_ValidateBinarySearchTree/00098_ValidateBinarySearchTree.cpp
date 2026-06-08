
#include <vector>
#include <cassert>
#include <optional>
#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// O(N) time, O(N) space for extra vector
class SolutionTreeTraversalExtraMem {
public:
    auto isValidBST(TreeNode* root) -> bool
    {
        if(!root || (!root->left && !root->right))
        {
            return true;
        }

        // Push back all values into a vector, then check the vector
        auto vals = std::vector<int>{};
        dfs(root,vals);

        // There must be at least two values due to the left & right check above.
        for(auto i = 1; i < vals.size(); ++i)
        {
            if(vals[i-1] >= vals[i])
            {
                return false;
            }
        }
        return true;
    }

    auto dfs(TreeNode* node, std::vector<int>& vals) -> void
    {
        if(!node) return;

        dfs(node->left, vals);
        vals.push_back(node->val);
        dfs(node->right, vals);
    }
};

// O(N) time, O(1) space
class SolutionTreeTraversalInPlace {
public:
    auto isValidBST(TreeNode* root) -> bool
    {
        if(!root || (!root->left && !root->right))
        {
            return true;
        }

        const auto& [isValid, min, max] = dfs(root);

        return isValid;
    }

    struct DfsContext
    {
        bool isValid{true};
        std::optional<int> min{std::nullopt};
        std::optional<int> max{std::nullopt};
    };

    auto dfs(TreeNode* node) -> DfsContext
    {
        if(!node)
        {
            assert(0);
        }

        auto min = node->val;
        auto max = node->val;

        auto leftContext = DfsContext{};
        auto isValidFromLeft = true;
        if(node->left)
        {
            leftContext = dfs(node->left);
            isValidFromLeft = leftContext.max.value() < node->val && leftContext.isValid;
            if(!isValidFromLeft) return {false,0,0}; // Can return false immediately if false.
            min = std::min(min,leftContext.min.value());
            max = std::max(max,leftContext.max.value());
        }

        auto rightContext = DfsContext{};
        auto isValidFromRight = true;
        if(node->right)
        {
            rightContext = dfs(node->right);
            isValidFromRight = rightContext.min.value() > node->val && rightContext.isValid;
            if(!isValidFromRight) return {false,0,0}; // Can return false immediately if false.
            min = std::min(min,rightContext.min.value());
            max = std::max(max,rightContext.max.value());
        }

        return {isValidFromLeft && isValidFromRight, min, max};
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto tn32 = TreeNode{32};
    auto tn26 = TreeNode{26};
    auto tn47 = TreeNode{47};
    auto tn19 = TreeNode{19};
    auto tn56 = TreeNode{56};
    auto tn27 = TreeNode{27};

    tn32.left = &tn26;
    tn32.right = &tn47;

    tn26.left = &tn19;
    tn47.right = &tn56;

    tn19.right = &tn27;

    auto iii = SolutionTreeTraversalInPlace{}.isValidBST(&tn32);
    auto i = 42;
    return 0;
}

