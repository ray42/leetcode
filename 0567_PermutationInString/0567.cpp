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


