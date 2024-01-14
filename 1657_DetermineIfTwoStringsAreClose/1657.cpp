/*
Medium: https://leetcode.com/problems/determine-if-two-strings-are-close/description/?envType=daily-question&envId=2024-01-14

Let's example the two operations:

Op1: Swap any two existing characters.
    For example, abcde -> aecdb (b and e swapped)

Op2: Transform every occurrence of one existing character into another existing character, 
     and do the same with the other character.

     For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

Op1 gives us the freedom we need to move characters around, so we only care if
we can make the frequencies of the characters the same under some condition.

What do I mean by make the frequencies the same under some condition?

Well, if we have something like:
aab and aba, since the frequencies of a (2) and b (1) are the same, then we know that we
can use op1 to make them equal.

HOWEVER, Op2 gives us the ability to swap the frequencies of two letters.
So if we have
aab and bab, then we can use Op2 on the first string to make:
bba, since now the frequencies of the letters of both of the string are the same, they are equal.

So if we think about it, all we for two strings to be considered close is for all the letters
to exist in both strings and the frequencies to be the same. Note that we do not need
the letters to have the correct frequencies since we can "swap" the frequencies by Op2.

Condition 1: make sure that all the letters exists in both the strings
Condition 2: make sure that the frequencies are the same

The constraints usually allow us to do something efficient, let's look at them:

1) 1 <= word1.length, word2.length <= 105
2) word1 and word2 contain only lowercase English letters.

Contraint 2 would allow us to use arrays indexed by str[x]-'a', where str[x] is a letters in str
*/

#include <string>
#include <array>
#include <algorithm>

class Solution {
public:
    bool closeStrings(const std::string& word1, const std::string& word2)
    {
        if(word1.size() != word2.size())
            return false;

        if(word1.empty()) return true;

        auto freq1 = std::array<int, 26>{};
        auto freq2 = std::array<int, 26>{};

        for(const auto& c : word1)
        {
            ++freq1[c-'a'];
        }

        for(const auto& c: word2)
        {
            if(freq1[c-'a'] == 0) // this letter does not exist in word1
            {
                return false;
            }

            ++freq2[c-'a'];
        }

        std::ranges::sort(freq1);
        std::ranges::sort(freq2);

        return freq1 == freq2;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

