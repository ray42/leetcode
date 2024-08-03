#include <vector>
#include <array>

class Solution {
public:
    bool canBeEqual(std::vector<int>& target, std::vector<int>& arr) 
    {
        auto freq = std::array<int,1001>{};
        for(const auto& i : target)
        {
            ++freq[i];
        }
        for(const auto& i : arr)
        {
            --freq[i];
        }
        for(const auto& i : freq)
        {
            if(i != 0)
            {
                return false;
            }
        }
        return true;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
