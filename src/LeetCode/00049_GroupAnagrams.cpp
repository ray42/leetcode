
#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution49 {
public:
  std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) const {

    auto groupedAnagrams = std::unordered_map<std::string, std::vector<std::string>>{};
    for (const auto& str : strs) {
      auto sortedStr = str;
      std::ranges::sort(sortedStr);
      groupedAnagrams[sortedStr].push_back(str);
    }

    auto ret = std::vector<std::vector<std::string>>{};

    for (const auto& [key, value] : groupedAnagrams) {
      ret.push_back(value);
    }

    // Can use this as well:
    //std::transform(groupedAnagrams.begin(), groupedAnagrams.end(),
    //    std::back_inserter(ret),
    //    [](const auto& pair) {
    //        return pair.second;
    //    });

    // C++23
    //return groupedAnagrams
    //    | std::views::values
    //    | std::ranges::to<std::vector>();

    return ret;
  }
};

// More efficient solution using character count as key instead of sorting the string
class Solution49_2 {
public:
  std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) const {

    // Custom hash for std::array
    struct ArrayHash {
      size_t operator()(const std::array<int, 26>& arr) const {
        size_t hash = 0;
        for (int i : arr) {
          hash = hash * 31 + std::hash<int>{}(i);
        }
        return hash;
      }
    };

    std::unordered_map<std::array<int, 26>, std::vector<std::string>, ArrayHash> grouped;

    for (const auto& str : strs) {
      std::array<int, 26> count{}; // all zeros

      for (char c : str) {
        count[c - 'a']++;
      }

      grouped[count].push_back(str);
    }

    std::vector<std::vector<std::string>> ret;
    ret.reserve(grouped.size());

    for (auto& [key, value] : grouped) {
      ret.push_back(std::move(value));
    }

    return ret;
  }
};