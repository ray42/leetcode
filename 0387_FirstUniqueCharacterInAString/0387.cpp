/*
Easy https://leetcode.com/problems/first-unique-character-in-a-string/description/
*/

#include <string>
#include <unordered_map>
#include <array>

class Solution {
public:
    auto firstUniqChar(const std::string& s) -> int
    {
        //auto freq = std::unordered_map<char, int>{};
        auto freq = std::array<int,26>{};
        for(const auto c : s)
        {
            ++freq[c - 'a'];
        }
        
        for(auto i = 0; i < s.size(); ++i)
        {
            if(freq[s[i] - 'a'] == 1)
            {
                return i;
            }
        }
        return -1;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

