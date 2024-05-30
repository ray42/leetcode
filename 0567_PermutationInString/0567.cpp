/*
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false

Constraints:

    1 <= s1.length, s2.length <= 104
    s1 and s2 consist of lowercase English letters.

--------------------

This seems quite easy.

We deploy the sliding window approach, but this time it's fixed size.
So what are the conditions. So we can count the frequencies of the characters in s1.
Then we can move the sliding window, counting the characters in the window!
*/

#include <string>
#include <unordered_map>
#include <array>


// The optimal method involves checking if the sliding window is a permutation in one check
// rather than checking arrays of size 26.
// We do this by keeping variable called "match", this will count how many matches there are between
// s1 and the sliding window (on s2). If match == 26, then the count of all characters match and we are done.
class Solution {
public:
    auto checkInclusion(const std::string& s1, const std::string& s2) -> bool
    {
        const auto s1Size = s1.size();
        const auto s2Size = s2.size();
        if(s1Size > s2Size)
        {
            return false;
        }
        
        // Count chars in s1 and the sliding window
        auto s1Frequency = std::array<int, 26>{};
        auto slidingWindow = std::array<int, 26>{};
        for(auto i = 0; i < s1Size; ++i)
        {
            ++s1Frequency[s1[i] - 'a'];
            ++slidingWindow[s2[i] - 'a'];
        }

        auto match = 0;
        for(auto i = 0; i < 26; ++i)
        {
            if(s1Frequency[i] == slidingWindow[i]) ++match;
        }
        
        auto L = 0;
        // This is starting R on one past the first sliding window
        for(auto R = s1Size; R < s2Size; ++R)
        {
            // This is comparing the previous sliding window
            if(match == 26) return true;
            
            // Increment the right
            auto i = s2[R] - 'a';
            ++slidingWindow[i];

            // But what are the consequences of incrementing the sliding window? What is the effect on match?
            // Well, if s1Frequency[i] == slidingWindow[i], then it means it wasn't equal before and the increment made it equal.
            // so we ++match
            //
            // if before it was equal and now it's not, then we --match. But we must be careful, we can't just do
            // s1Frequency[i] != slidingWindow[i], since it could have been not equal before and not equal now.
            // Do we must check if s1Frequency[i] == slidingWindow[i] + 1, which implies that our increment of slidingWindow[i] have caused it to be greater than
            // s1Frequency[i] by one, which means that they were equal before.
            if(s1Frequency[i] == slidingWindow[i])
            {
                ++match;
            }
            else if(s1Frequency[i] +1 == slidingWindow[i])
            {
                --match;
            }

            // Now remove the character pointed to by L from the sliding window and do the same logic
            i = s2[L] - 'a';
            --slidingWindow[i];
            if(s1Frequency[i] == slidingWindow[i])
            {
                ++match;
            }
            else if(s1Frequency[i] -1 == slidingWindow[i])
            {
                // So we have decremented slidingWindow[i], we want to know if it was equal to s1Frequency before being decremented.
                // We check this by decrementing s1Frequency[i] , if it does match the now decremented slidingWindow[i], then we know
                // it was equal before and now we don't have a match.
                --match;
            }

            ++L;
        }
        
        // Remember that in the loop, we check the previous sliding window and then set up the current one?
        // So we need to check the last (current) one.
        return match == 26;
    }
};


// OKAY, so this is not optimal, it's O(26*N), let's do the optimal way, see above
class SolutionO26N {
public:
    auto checkInclusion(const std::string& s1, const std::string& s2) -> bool
    {
        const auto s1Size = s1.size();
        const auto s2Size = s2.size();
        if(s1Size > s2Size)
        {
            return false;
        }
        
        auto s1Frequency = std::array<int, 26>{};
        for(const auto& c : s1)
        {
            ++s1Frequency[c - 'a'];
        }
        
        // Calculate the frequency for the first sliding window
        auto slidingWindow = std::array<int, 26>{};
        for(auto i = 0; i < s1Size; ++i)
        {
            ++slidingWindow[s2[i] - 'a'];
        }

        auto L = 0;
        // This is starting R on one past the first sliding window
        for(auto R = s1Size; R < s2Size; ++R)
        {
            // This is comparing the previous sliding window
            if(s1Frequency == slidingWindow) return true;
            
            // Increment the right
            ++slidingWindow[s2[R] - 'a'];
            // Decrement the left
            --slidingWindow[s2[L] - 'a'];

            ++L;
        }
        
        // Remember that in the loop, we check the previous sliding window and then set up the current one?
        // So we need to check the last (current) one.
        return s1Frequency == slidingWindow;
    }
};


// This is meh because the logic is correct but I could have done it much better
class SolutionMeh {
public:
    auto checkInclusion(const std::string& s1, const std::string& s2) -> bool
    {
        const auto s1Size = s1.size();
        const auto s2Size = s2.size();
        if(s1Size > s2Size)
        {
            return false;
        }
        
        //auto s1Frequency = std::unordered_map<char,int>{};
        auto s1Frequency = std::array<int, 26>{};
        for(const auto& c : s1)
        {
            ++s1Frequency[c - 'a'];
        }

        // Calculate the frequency for the first sliding window
        //auto s2Frequency = std::unordered_map<char,int>{};
        auto s2Frequency = std::array<int, 26>{};
        for(auto i = 0; i < s1Size-1; ++i)
        {
            ++s2Frequency[s2[i] - 'a'];
        }

        auto L = 0;
        for(auto R = s1Size - 1; R < s2Size; ++R)
        {
            ++s2Frequency[s2[R] - 'a'];
            if(s1Frequency == s2Frequency) return true;

            --s2Frequency[s2[L] - 'a'];
            ++L;
        }

        return false;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto aaaa = Solution{}.checkInclusion("ab", "eidbaooo");
    return 0;
}


