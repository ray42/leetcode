/*
EASY https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/description/

RayNotes
  OKAY, so the 1 operation is to basically move 1 character from any position in string i to any position in string j
  Given such a free and unrestricted operation, if it is possible to make all strings equal, then we CAN make all strings equal.
    that is, if the operation is something like "take the last char of string i and put it in front of string j" - then we have a lot to consider
    since even if all the characters are there, due to the restricted operation, we may not be able to make all string equal.

  This gives us some insight - all we need to do is, confirm that we can make all strings equal in `words`
  But what does that mean? Due to the unstrictiveness of the above operation, if we can satisfy that all
  strings have the same characters, we are OK - then the operation can just move them to the correct place.
*/
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    auto makeEqual(const std::vector<std::string>& words) -> bool
    {
        // Edge case
        if(words.size() == 1) return true;

        auto characterFrequencies = std::unordered_map<char, int>{};

        for(const auto& word : words)
        {
            for(const auto& c : word)
            {
                ++characterFrequencies[c];
            }
        }

        const auto numberOfWords = words.size();
        for(const auto& [character, frequency] : characterFrequencies)
        {
            if(frequency % numberOfWords) return false;
        }

        return true;
    }
};

auto main(int argc, char* argv[]) -> int
{

    return 0;
}
