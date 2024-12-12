/*


*/

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <string_view>
#include <utility>

class SolutionRecursiveDfs {

private:

    struct TrieNode
    {
        bool isWord{false};
        std::unordered_map<char, std::unique_ptr<TrieNode>> children{};
    };

    auto add(TrieNode& root, std::string_view word)
    {
        auto curr = &root;
        for(const auto c : word)
        {
            if(!curr->children.contains(c))
            {
                curr->children.insert({c, std::make_unique<TrieNode>()});
            }
            curr = curr->children[c].get();
        }

        curr->isWord = true;
    }

public:

    auto findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) -> std::vector<std::string>
    {
        // Build the trie
        auto root = TrieNode{};
        for(const auto& word : words)
        {
            add(root,word);
        }

        // Loop through cells in board and perform DFS
        const auto nrow = board.size();
        const auto ncol = board[0].size();

        const auto dr = std::vector<int>{-1,1};
        const auto dc = std::vector<int>{-1,1};

        auto currentWord = std::string{};
        auto result = std::unordered_set<std::string>{};
        
        auto dfs = [&](auto&& dfs, int r, int c, TrieNode* curr)
        {
            // If r and c are out of bounds or the letter doesn't exist in the children of root, then return
            // because there is no need to continue on this path.
            if(r < 0 || r == nrow || c < 0 || c == ncol || board[r][c] == '\0' || !curr->children.contains(board[r][c]) )
            {
                return;
            }

            auto oldChar = board[r][c];

            currentWord.push_back(oldChar);
            board[r][c] = '\0';

            if(curr->children[oldChar]->isWord)
            {
                result.insert(currentWord);
            }

            // Visit all four directions
            dfs(dfs, r+1, c, curr->children[oldChar].get());
            dfs(dfs, r-1, c, curr->children[oldChar].get());
            dfs(dfs, r, c+1, curr->children[oldChar].get());
            dfs(dfs, r, c-1, curr->children[oldChar].get());

            // backtrack
            board[r][c] = oldChar;
            currentWord.pop_back();
        };

        for(auto r = 0; r < nrow; ++r)
        {
            for(auto c = 0; c < ncol; ++c)
            {
                dfs(dfs, r, c, &root);
            }
        }

        // return the list of elements from "words" that exists in board.
        return std::vector<std::string>(result.begin(), result.end());
    }
};




auto main(int argc, char* argv[]) -> int
{

    auto board = std::vector<std::vector<char>>{
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}};
    auto words = std::vector<std::string>{"oath","pea","eat","rain"};

    auto iii = SolutionRecursiveDfs{}.findWords(board, words);
    auto iiii = 42;
    return 0;
}



