/*
MEDIUM https://leetcode.com/problems/group-anagrams/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    auto groupAnagrams(std::vector<std::string>& strs) -> std::vector<std::vector<std::string>>
    {
        // We need to group the arrays together using a common key. We can do this by sorting the keys!
        auto groupedAnangram = std::unordered_map<std::string,std::vector<std::string>>{};
        for(auto& str : strs)
        {
            auto key = str;
            std::ranges::sort(key);
            groupedAnangram[key].push_back(std::move(str));
        }

        // Now we need to return the values
        auto ret = std::vector<std::vector<std::string>>{};
        for(auto& [key, anagramVec] : groupedAnangram)
        {
            ret.push_back(std::move(anagramVec));
        }

        return ret;
    }
};


auto main(int argc, char* argv[]) -> int
{
    std::cout << "test" << std::endl;
    return 0;
}













