/*
The thing I need to get my head around when implementing a trie is that 
1) a letter exists is there is a [letter <-> TrieNode pair] pair.
Example: Let's say that we are trying to find the word "AB".
If it exists, then we must have the following structure:

RootNode:
 map[
 (A,TrieNodeA)
 ]

  TrieNodeA
  map[
  (B,TrieNodeB)
  ]


Also, we'll need a boolean in each word to indicate if this is the end of a word.
Otherwise, if we insert a word such as "bedroom" and we want to find the word "bed",
the word "bed" hasn't been inserted, so we should return false. But how do we know?

That is, without something to signify that it's the end of a word, inserting "bedroom" will overshadow "bed",
and we have no way to tell if "bed" is inserted or not.

Given this, we can code up the trie
*/

#include <unordered_map>
#include <string>
#include <memory>

class Trie {
private:

    struct TrieNode
    {
        bool isWordEnd{false};
        std::unordered_map<char,std::unique_ptr<TrieNode>> children{};
    };

    TrieNode root{};

public:

    Trie() = default;
    
    auto insert(const std::string& word) -> void
    {
        auto curr = &root;
        for(const auto c : word)
        {
            if(!curr->children.contains(c))
            {
                curr->children.insert({c,std::make_unique<TrieNode>()});
            }
            curr = curr->children[c].get();
        }

        // curr now is the value of the [char,trieNode] pair at the end of the node.
        // We want to say that this is the end of a word.
        curr->isWordEnd = true;
    }
    
    // Only return true is a whole word has been previous inserted, i.e. we end with a trienode with isWordEnd = true
    auto search(const std::string& word) -> bool
    {
        auto curr = &root;
        for(auto c : word)
        {
            if(!curr->children.contains(c))
            {
                return false;
            }
            curr = curr->children[c].get();
        }
        return curr->isWordEnd;
    }
    
    auto startsWith(const std::string& prefix) -> bool
    {
        auto curr = &root;
        for(auto c : prefix)
        {
            if(!curr->children.contains(c))
            {
                return false;
            }
            curr = curr->children[c].get();
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */




auto main(int argc, char* argv[]) -> int
{
    return 0;
}

