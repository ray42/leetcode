/*
EASY https://leetcode.com/problems/valid-anagram/

RayNotes: We just need to make sure that the frequency of characters in both strings are the same.

BONUS: Use only 1 map.

*/

#include <string>
#include <unordered_map>
#include <array>

class Solution {
public:
    auto isAnagram(const std::string& s, const std::string& t) -> bool
    {
        auto frequencyMap = std::unordered_map<char,int>{}; // RRR42ANKI, this is what I keep failing to remember - only use one map

        for(const auto& c : s)
        {
            ++frequencyMap[c];
        }
        for(const auto& c : t)
        {
            --frequencyMap[c];
        }

        for(const auto&[c,frequency] : frequencyMap)
        {
            if(frequency != 0) return false;
        }
        return true;
    }
};


class Solution2 {
public:
    auto isAnagram(const std::string& s, const std::string& t) -> bool
    {
        auto frequencyMap = std::unordered_map<char,int>{}; 

        for(const auto& c : s)
        {
            ++frequencyMap[c];
        }
        for(const auto& c : t)
        {
            --frequencyMap[c];
        }

        for(const auto&[c,frequency] : frequencyMap)
        {
            if(frequency != 0) return false;
        }
        return true;
    }
};

class Solution3 {
public:
    auto isAnagram(const std::string& s, const std::string& t) -> bool
    {
        if(s.size() != t.size())
        {
            return false;
        }

        auto frequency = std::array<int,26>{};
        for(const auto& c : s)
        {
            ++frequency[c - 'a'];
        }
        for(const auto& c : t)
        {
            if(--frequency[c - 'a'] < 0)
            {
                return false;
            }
        }

        return true;
    }
};

auto main(int argc, char* argv[])->int
{
    Solution3{}.isAnagram("rat","car");
    return 0;
}