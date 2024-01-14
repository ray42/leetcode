/*
MEDIUM: https://leetcode.com/problems/top-k-frequent-elements/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <algorithm>
#include <ranges>

std::vector<int> topKFrequent(const std::vector<int>& nums, int k) 
{
    // 1) Count the frequency per elements, store this in an unordered_map where key = the number, val = frequency
    // 2) Insert this map into a vector of pairs. The pairs should be unique because the key of the map is unique.
    // 3) Sort this vector using the second of the pair.
    auto numberToFrequency = std::unordered_map<int,int>{};
    for(const auto& i : nums)
    {
        numberToFrequency[i]++;
    }

    //using PairType = decltype(numberToFrequency)::value_type;
    using PairType = std::pair<int,int>;

    auto vecValFreq = std::vector<PairType>{numberToFrequency.begin(), numberToFrequency.end()};

    std::ranges::sort(vecValFreq, [](const PairType& left, const PairType& right)
    {
        return left.second > right.second;
    });

    auto ret = std::vector<int>{};
    //for(auto i : std::ranges::views::iota(0,k)) // Leetcode doesn't seem to support ranges::views yet...
    for(auto i = 0; i < k; ++i)
    {
        ret.push_back(vecValFreq[i].first);
    }
    return ret;
 }

template<typename T>
auto print(const std::vector<T>&v)
{
    auto ss = std::stringstream{};
    ss << "[";
    for(const auto& i : v)
    {
        ss << i << ",";
    }
    ss << "]";
    return ss.str();
}

auto main()->int
{
    auto res = topKFrequent({1,2},1);
    std::cout << print(res) << "\n";
    std::cout << "hello ray!" << std::endl;
}
