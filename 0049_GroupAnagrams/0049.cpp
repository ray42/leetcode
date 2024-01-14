/*
MEDIUM https://leetcode.com/problems/group-anagrams/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) 
{
    // Key is sorted string
    auto m = std::unordered_map<std::string, std::vector<std::string>>{};
    for(auto& str : strs)
    {
        auto key = str;
        std::ranges::sort(key);
        m[key].push_back(std::move(str));
    }

    auto ret = std::vector<std::vector<std::string>>{};

    for(auto& [key, val] : m)
    {
        ret.push_back(std::move(val));
    }

    return ret;
}

int main()
{
    std::cout << "test" << std::endl;
    return 0;
}
