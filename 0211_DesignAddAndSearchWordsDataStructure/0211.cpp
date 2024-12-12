
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class WordDictionary {

    struct TrieNode
    {
        bool isWordEnd{false};
        std::unordered_map<char,std::unique_ptr<TrieNode>> children{};
    };

    TrieNode root{};

public:
    
    WordDictionary() = default;
    
    void addWord(const std::string& word)
    {
        auto curr = &root;
        for(const auto& c : word)
        {
            if(!curr->children.contains(c))
            {
                curr->children.insert({c, std::make_unique<TrieNode>()});
            }
            curr = curr->children[c].get();
        }

        curr->isWordEnd = true;
    }
    
    bool search(const std::string& word)
    {
        auto helper = [&](auto&& helper, TrieNode* node, int root) -> bool
        {
            auto curr = node;
            for(auto i = root; i < word.size(); ++i)
            {
                if(word[i] == '.')
                {
                    for(const auto&[c, child] : curr->children)
                    {
                        if(helper(helper,child.get(), i + 1))
                        {
                            return true;
                        }
                    }
                    
                    return false;
                }
                else if(!curr->children.contains(word[i]))
                {
                    return false;
                }
                curr = curr->children[word[i]].get();
            }
            
            return curr->isWordEnd;
        };

        auto res = helper(helper,&root,0);
        return res;
    }
};


class TrieNode {
public:
    std::vector<TrieNode*> children;
    bool word;

    TrieNode() : children(26, nullptr), word(false) {}
};



auto main(int argc, char* argv[])->int
{
    auto dict = WordDictionary2{};
    
    
    dict.addWord("bad");
    //dict.addWord("dad");
    //dict.addWord("mad");
    //dict.search("pad");
    //dict.search("bad");
    //dict.search(".ad");
    dict.search("b..");
    // */

    /*
    dict.addWord("a");
    dict.search("a.");
    */




    return 0;
}

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */