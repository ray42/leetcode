/*
Easy https://leetcode.com/problems/largest-substring-between-two-equal-characters/description/

RAYNOTES:

# FIRST ATTEMPT

"" -> -1
"a" -> -1
"aa" -> 0
"aba" -> 1
"aaa" -> 1
"abca" -> 2
"aaaa" -> 2

Let's ignore the first two edge cases, it's evident that we have to 
keep track of the first and last position of each occurrence of a letter we come across.
E.g. in "aaaa" , the first pos of `a` is 0, the last pos of `a` is 3
3-0 = 3. And we subtract 1 to get the length in between.

In fact, we do better, we don't even need to keep track of the last position. We can just keep track of the
first position and the length.

What if we only have one 'a' in a string and more other letters?
"abcd", then the first and last pos of 'a' will be 0. The length calculated would be: 0-0-1 = -1.
This is OK, since it signifies no character that appears twice, see the example above.

What can we use to keep track of all these first position and lengths?
A hash map where the key is the character and the value is a struct{firstPos, maxLength}.

###################################

Now that I think about it, I don't need to store the maxLength per char, nor do I need to store the position
of successive character. I only need to store the initial position of a character, then
as I come across successive ones, I update the overall maxLength.

Given this, we can store the initial positions in an array. See solution2 below.

*/
#include <string>
#include <unordered_map>
#include <array>
#include <algorithm>

class Solution1 {
public:
    struct PosLen
    {
        int firstPos = 0;
        int maxLength = -1;
    };
    int maxLengthBetweenEqualCharacters(const std::string& s) 
    {
        if(s.size() < 2) return -1;

        auto positionAndMaxLength = std::unordered_map<char, PosLen>{};
        auto maxLen = -1;
        for(auto i = 0; i < s.size(); ++i)
        {
            const auto& c = s[i];
            if(auto it = positionAndMaxLength.find(s[i]); it == positionAndMaxLength.end())
            {
                positionAndMaxLength.emplace(c, PosLen{i,-1});
            }
            else
            {
                auto& posLen = positionAndMaxLength[c];
                posLen.maxLength = i - posLen.firstPos - 1;
                if(posLen.maxLength > maxLen) maxLen = posLen.maxLength;
            }
        }
        return maxLen;
    }
};

class Solution2 
{
public:

    int maxLengthBetweenEqualCharacters(const std::string& s) 
    {
        if(s.size() < 2) return -1;
        
        auto initialPositions = std::array<int, 26>{};
        std::ranges::fill(initialPositions,-1);

        auto maxLen = -1;
        for(auto i = 0; i < s.size(); ++i)
        {
            const auto& c = s[i];

            // Index into initialPositions
            const auto ci = c - 'a'; // We can do this because "s contains only lowercase English letters".

            // If this is the first time we have seen c, then set it's initial position.
            if(initialPositions[ci] == -1) 
            {
                initialPositions[ci] = i;
            }
            else
            {
                // Conditionally update maxLen
                auto currentLen = i - initialPositions[ci] - 1;
                maxLen = std::max(currentLen, maxLen);
            }
        }
        return maxLen;
    }
};

auto main(int argc, char* argv[]) -> int
{
  return 0;
}





