/*
Medium https://leetcode.com/problems/sort-characters-by-frequency/description/
*/

#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>

// NOTE: Do this again but with a priority queue
// https://leetcode.com/problems/sort-characters-by-frequency/solutions/4689154/beats-100-users-c-java-python-javascript-2-approaches-explained/

class Solution 
{
public:
    auto frequencySort(std::string& s) -> std::string
    {
        // 1) Count the frequencies per character
        // 2) Sort by frequency
        // 3) Print out a string using the frequencies

        // 1) Count the frequencies per character
        auto freq = std::unordered_map<char,int>{};
        for(const auto c : s)
        {
            ++freq[c];
        }

        // Convert the map into a vector and sort by frequency
        auto vecFreq = std::vector<std::pair<char,int>>(freq.begin(),freq.end());
        std::ranges::sort(vecFreq, [](const std::pair<char,int>& lhs, const std::pair<char,int>& rhs){
            return lhs.second > rhs.second;
        });

        // Now build the string. We can re-use the input string.
        auto i = 0;
        for(const auto& [c, freq] : vecFreq)
        {
            for(auto j = 0; j < freq; ++j)
            {
                s[i++] = c;
            }
        }

        return s;
    }
};

auto main(int argc, char* argv) -> int
{
    return 0;
}

