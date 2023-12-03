
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once. 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:

Input: strs = [""]
Output: [[""]]

Example 3:

Input: strs = ["a"]
Output: [["a"]]
*/

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
