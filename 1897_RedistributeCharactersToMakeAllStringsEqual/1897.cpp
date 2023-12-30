/*
EASY https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/description/

You are given an array of strings words (0-indexed).
In one operation, pick two distinct indices i and j, where words[i] is a non-empty string, and move any character from words[i] to any position in words[j].
Return true if you can make every string in words equal using any number of operations, and false otherwise.

Example 1:

Input: words = ["abc","aabc","bc"]
Output: true
Explanation: Move the first 'a' in words[1] to the front of words[2],
to make words[1] = "abc" and words[2] = "abc".
All the strings are now equal to "abc", so return true.

Example 2:

Input: words = ["ab","a"]
Output: false
Explanation: It is impossible to make all the strings equal using the operation.

Constraints:
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists of lowercase English letters.


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
