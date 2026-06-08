#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    auto findLeastNumOfUniqueInts(const std::vector<int>& arr, int k) -> int
    {
        if(k >= arr.size())
        {
            return 0;
        }
        
        // Calculate the frequencies (freq)
        // Sort by frequencies
        // Remove elements in freq depending on frequency and count how many elements
        auto freq = std::unordered_map<int,int>{};
        for(const auto& a : arr)
        {
            ++freq[a];
        }
        
        auto sortedFreq = std::vector<std::pair<int,int>>(freq.begin(),freq.end());

        std::ranges::sort(sortedFreq, 
        [](decltype(sortedFreq)::value_type lhs, decltype(sortedFreq)::value_type rhs)
        {
            // first is the number, second is the frequency
            return lhs.second < rhs.second;
        });

        // Now get the prefix sum
        for(auto i = 1; i < sortedFreq.size(); ++i)
        {
            sortedFreq[i].second = sortedFreq[i-1].second + sortedFreq[i].second;
        }
        
        // Now loop through to see how many numbers we can wipe out before we get to one where we have some numbers left.
        for(auto i = 0; i < sortedFreq.size(); ++i)
        {
            // We have found a number which we couldn't wipe out. So count how many unique numbers there are from here to the end.
            if(sortedFreq[i].second - k > 0)
            {
                return sortedFreq.size() - i;
            }
        }

        return -1;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

