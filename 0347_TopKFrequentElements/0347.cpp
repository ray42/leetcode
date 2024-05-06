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



class Solution {
public:
    auto topKFrequent(const std::vector<int>& nums, int k) -> std::vector<int>
    {
        
    }
};

// O(n) solution
class Solution2 {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> mp;
        int topFreq = 0;
        for(int x: nums) {
            mp[x]++;
            topFreq = std::max(topFreq, mp[x]);
        }

        std::vector<int> ans;

        std::unordered_map<int, std::vector<int>> freqMap;
        for(auto it: mp) {
            freqMap[it.second].push_back(it.first);
        }

        int count=0;

        while(count<k) {
            if(freqMap.find(topFreq) != freqMap.end()) {
                std::vector<int> v = freqMap[topFreq];
                int n = v.size();
                for(int i=0; i<n; i++) {
                    ans.push_back(v[i]);
                    count++;
                    if(count == k)
                        break;
                }
            }
            topFreq--;
        }

        return ans;
    }
};


auto main()->int
{
    auto res = topKFrequent({1,2},1);
    std::cout << print(res) << "\n";
    std::cout << "hello ray!" << std::endl;
}
