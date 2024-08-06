
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::string kthDistinct(std::vector<std::string>& arr, int k)
    {
        auto freq = std::unordered_map<std::string,int>{};
        for(const auto& s : arr)
        {
            ++freq[s];
        }

        for(const auto& s : arr)
        {
            if(freq[s] == 1)
            {
                --k;
                if(k == 0)
                {
                    return s;
                }
            }
        }
        return "";
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

