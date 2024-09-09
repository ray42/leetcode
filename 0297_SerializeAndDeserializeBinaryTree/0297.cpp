#include <string>
#include <functional>
#include <memory>
#include <sstream>

/*
There is no single binary tree traversal that uniquely describes a tree.
E.g. if we have a tree degenerate to the left or degenerate to the right, then
pre or post order traversal cannot uniquely describes the tree.

With inorder, you don't even know where the leaves are, so how do you know if you need to go back up or continue doing the left/right leaves?

So, we can use preorder DFS but mark out where the nulls are. Let's do this!


Example, let's say we have
  1
 / \
2   3
   / \
  4   5

Let's do preorder and use N to signify a null node (a leaf):

[1,2,N,N,3,4,N,N,5,N,N]

Given the preorder traversal with leaves, can we re-generate the tree? Yes, we just keep going as deep as we can, DFS manner.

     1
   /   \
  2     3
 / \   / \
      4   5
     / \ / \

So we can. Let's implement
*/



//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    static constexpr std::string_view NullString = "N,";

    // Encodes a tree to a single string.
    auto serialize(TreeNode* root) -> std::string
    {
        auto ret = std::string{};
        auto dfs = std::function<void(TreeNode*)>{};

        dfs = [&ret, &dfs](TreeNode* node)
        {
            if(!node)
            {
                ret.append(NullString);
                return;
            }

            ret.append(std::to_string(node->val) + ",");

            dfs(node->left);
            dfs(node->right);
        };

        dfs(root);

        ret.pop_back();

        return ret;
    }

    auto buildTree(const std::vector<std::string>& v, int& i) -> TreeNode*
    {
        if(v[i] == "N")
        {
            ++i;
            return nullptr;
        }

        auto n = new TreeNode{std::stoi(v[i])};
        ++i;

        n->left = buildTree(v, i);
        n->right = buildTree(v, i);

        return n;
    }

    // Decodes your encoded data to tree.
    auto deserialize(const std::string& data) -> TreeNode *
    {
        // We know that we need to loop through data and then build the tree in a DFS manner.
        // To make things easier for myself. I'm going to split it up first.

        auto tokens = std::vector<std::string>{};
        auto token = std::string{};
        auto ss = std::istringstream{data};
        while(std::getline(ss, token, ','))
        {
            tokens.push_back(token);
        }

        // Now we loop through tokens create the tree in a DFS sense.
        auto i = 0;
        auto ret = buildTree(tokens,i);
        return ret;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

auto main(int argc, char* argv[]) -> int
{
    auto n1 = std::make_unique<TreeNode>(1);
    auto n2 = std::make_unique<TreeNode>(2);
    auto n3 = std::make_unique<TreeNode>(3);
    auto n4 = std::make_unique<TreeNode>(4);
    auto n5 = std::make_unique<TreeNode>(5);
    n1->left = n2.get();
    n1->right = n3.get();

    n3->left = n4.get();
    n3->right = n5.get();

    auto C = Codec{};
    auto iii = C.deserialize(C.serialize(n1.get()));

    auto ii = 42;
}

