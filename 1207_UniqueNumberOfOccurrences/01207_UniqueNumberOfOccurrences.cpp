/*
Easy: https://leetcode.com/problems/unique-number-of-occurrences/description/
*/
#include <vector>

#include <bitset>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Solution 
{
public:

    // Overall:
    // Time: O(n)
    // Space: O(n) - for the set and frequency 
    auto uniqueOccurrences(const std::vector<int>& arr) -> bool
    {
        auto frequency = std::unordered_map<int,int>{};
        for(const auto& num : arr) // O(n)
        {
            ++frequency[num]; // O(1)
        }
        auto set = std::unordered_set<int>{};
        for(const auto&[val, freq] : frequency)// O(n)
        {
            if(!set.emplace(freq).second)// O(1)
            {
                return false;
            }
        }
        return true;
    }
};

auto main(int argc, char* argv[])-> int
{
    auto ii = std::vector<std::pair<std::string,int>>{{"1",1},{"1",1},{"2",1},{"3",1},{"4",1},{"4",2},{"4",3},{"4",4},{"5",5}};
    auto um = std::unordered_map<std::string,int>(ii.begin(), ii.end());
    

    // range constructor
    std::vector<std::pair<std::bitset<8>, int>> v = {{0x12, 1}, {0x01,-1}};
    std::unordered_map<std::bitset<8>, double> m5(v.begin(), v.end());

    auto fdss = 42;

    return 0;
}
