#include <algorithm>
#include <string>
#include <iterator>


class Solution {
public:
    std::string maximumOddBinaryNumber(std::string& s) 
    {
        if(s.size() == 1) return s;

        // s = 01010
        // Move all '1's to the front
        auto ret = std::ranges::remove(s, '0');
        // s = 11110
        //     S  Rr
        // R-S = 3

        // Now overwrite the last 1 with 0 and 
        // write the 1 in the last position of s.
        // i.e. 11110 <- the 4th 1 becomes 0 and we write 1 in the last position
        for(auto i = std::distance(s.begin(), ret.begin()) - 1; i < s.size()-1; ++i)
        {
            s[i] = '0';
        }
        s.back() = '1';

        return s;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto str = std::string{"010"};
    auto sss = Solution{}.maximumOddBinaryNumber(str);
    return 0;
}


