/*
EASY https://leetcode.com/problems/destination-city/

*/

#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    auto destCity(const std::vector<std::vector<std::string>>& paths) -> std::string
    {
        auto pathMap = std::unordered_map<std::string, std::string>{};
        for(const auto& path : paths)
        {
            pathMap[path[0]] = path[1];
        }

        auto destCity = paths[0][1];
        while(true)
        {
            if(auto it = pathMap.find(destCity); it != pathMap.end())
            {
                destCity = it->second;
            }
            else
            {
                break;
            }
        }
        return destCity;
    }
};

auto main(int argc, char * argv[]) -> int
{
    return 0;
}