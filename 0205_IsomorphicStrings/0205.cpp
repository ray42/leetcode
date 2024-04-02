#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iterator>

// I did this wrong. Come back to it.
class Solution {
public:
    auto isIsomorphic(const std::string& s, const std::string& t) -> bool
    {
        // Count the frequencies
        auto umS = std::unordered_map<char,int>{};
        for(auto c : s)
        {
            ++umS[c];
        }
        auto vecS = std::vector<int>{};
        std::transform(umS.begin(), umS.end(), std::back_inserter(vecS), 
        [](const auto& p){ return p.second;});

        auto umT = std::unordered_map<char,int>{};
        for(auto c : t)
        {
            ++umT[c];
        }
        auto vecT = std::vector<int>{};
        std::transform(umT.begin(), umT.end(), std::back_inserter(vecT), 
        [](const auto& p){ return p.second;});

        std::ranges::sort(vecS);
        std::ranges::sort(vecT);

        if(vecS != vecT)
        {
            return 0;
        }

        // Now check the ordering.


        auto iii = 42;


        //auto umT = std::unordered_map<char,int>{};

        return true;


    }
};


auto main(int argc, char* argv[]) -> int
{
    auto ss = Solution{}.isIsomorphic("abbc","abc");
    return 0;
}
