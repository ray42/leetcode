#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]

Constraints:

    1) 1 <= nums.length <= 105
    2) -104 <= nums[i] <= 104
    3) k is in the range [1, the number of unique elements in the array].
    4) It is guaranteed that the answer is unique.

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    // 1) Count the frequency per elements, store this in an unordered_map where key = the number, val = frequency
    // 2) insert into a map where the frequency is key, key = value
    // 3) Loop backwards through the map for the first k elements.
    auto um = std::unordered_map<int,int>{};
    for(const auto& i : nums)
    {
        um[i]++;
    }

    auto map = std::map<int,int>{};
    for(const auto& [num, frequency] : um)
    {
        map.emplace(frequency,num);
    }

    int i = 0;
    auto ret = std::vector<int>{};
    for(auto it = map.rbegin(); it != map.rend(); ++it)
    {
        if(i == k) break;

        ret.push_back(it->second);

        ++i;
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
