/*
Given a string s, find the length of the longest substring without repeating characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:

    0 <= s.length <= 5 * 104
    s consists of English letters, digits, symbols and spaces.

////////////////////////////////////

We could generate all the substrings and then check to see which substrings contain non-repeating characters and keep track of the max length.
However, we will use a 2 pointer approach.

*/


#include <string>
#include <unordered_set>

class SolutionBruteForce {
public:
    // Generate all substrings. Check if every char in the substring is unique, if it is, update the max length
    // Small opimisation:
    // When generating all the substrings, we do so by generating all substrings starting at i = 0, ... i < s.size();
    // However, if we find that there is a repeating character in position j in a substring starting at i, then there is no
    // need to test substrings starting at i any further (since we know they will all contain at least that one repeating character).
    // Time = O(n^2/2) = O(n^2)
    // Space = O(1)
    auto lengthOfLongestSubstring(const std::string& s) -> int
    {
        // Generate all the substrings by starting at i, going to j
        const auto sSize = s.size();
        auto maxLength = 0;
        for(auto i = 0; i < sSize; ++i)
        {
            // Set up hash for the new word
            auto dupes = std::unordered_set<char>{};
            auto currentLength = 0;

            for(auto j = i; j < sSize; ++j)
            {
                if(auto res = dupes.insert(s[j]); res.second)
                {
                    // Increase the current length
                    ++currentLength;
                }
                else
                {
                    // because there is no point continuing to test strings starting from i
                    break;
                }
            }

            maxLength = std::max(currentLength, maxLength);
        }

        return maxLength;
    }
};


// Now we do the optimise solution with a two pointer approach - the sliding window
// The key to the sliding window is to determine the conditions for which we slide the window.
// Let's say we start with the L and R pointer at pos = 0.
//             01234567
// Input: s = "abcabcbb"
//             L
//             R
// When do we move L and R?
// Well, we keep moving R until we see a duplicate
//
//             01234567
// Input: s = "abcabcbb"
//             L
//                R
// So we know that abca isn't valid. How should we move L? It may be tempting to move L to where the duplicate is:
//
//             01234567
// Input: s = "abcabcbb"
//                L
//                R
// And continue on the algorithm by moving R. But what is all digits are unique except for the two a's?
// Imagine that the x's are all unique:
// 
//             01234567
// Input: s = "axxaxxxx"
//                L
//                R
// our algorithm will end up with the window:
// 
//             01234567
// Input: s = "axxaxxxx"
//                L
//                    R
// When it's obvious that the longest substring without repeating characters is 
//             01234567
// Input: s = "axxaxxxx"
//              L
//                    R
// So when we hit a duplicate:
//             01234567
// Input: s = "axxaxxxx"
//             L
//                R
// we need to move the L pointer past the duplicate:
//             01234567
// Input: s = "axxaxxxx"
//              L
//                R
// and continue on moving R, and repeat.
// So how is this implements. Moving R is easy, we can just put characters in a set.
// so when we hit a duplicate, we have a pointer to the second a.
// we can move L until it's equal to a, then go one after... let's see!
class Solution {
public:
    auto lengthOfLongestSubstring(const std::string& s) -> int
    {
        auto L = 0;
        auto R = 0;
        auto maxLen = 0;
        auto dupes = std::unordered_set<char>{};
        //auto ssss = dupes.insert('s');
        //auto sss = *ssss.first;
        const auto sSize = s.size();
        while(L < sSize && R < sSize)
        {
            if(auto res = dupes.insert(s[R]); res.second)
            {
                // We can insert, so move R to the next place
                maxLen = std::max(maxLen,R-L+1);
                ++R;
            }
            else
            {
                // We cannot insert, so we move L to one past the dupe
                while(s[L] != *res.first)
                {
                    // This is important because we may havve stuff like
                    // tmmzuxt, so the first dupe we come across is mm, if we just move the pointers but do not get rid of the t, then we will miss the
                    // t at the end, so we'll get length = 4 instead of 5.
                    dupes.erase(s[L]);
                    ++L;
                }
                // Now L is at the first dupe, let's go one past it.
                ++L;
                ++R; // this needs to be moved since is still at the second dupe which we know is already in the set.
            }
        }

        return maxLen;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto sss = Solution{}.lengthOfLongestSubstring("tmmzuxt");
    return 0;
}



