/*
Medium: https://leetcode.com/problems/number-of-laser-beams-in-a-bank/description/

RayNotes:

The number of lasers between two layers is just the number of devices of each layer multiplied by each other.
So, I just need to go through each layer and multiply the number of devices with the previous number of devices,
skipping any empty rows.

*/

#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    auto numberOfBeams(const std::vector<std::string>& bank) -> int
    {
        const auto numRow = bank.size();
        auto numLasers = 0;

        auto previousNumDevices = 0;
        
        for(auto rowi = 0; rowi < numRow; ++rowi)
        {
            auto currentNumDevices = std::ranges::count(bank[rowi], '1');

            if(currentNumDevices == 0) continue;

            if(previousNumDevices != 0)
            {
                numLasers += previousNumDevices * currentNumDevices;
            }

            previousNumDevices = currentNumDevices;
        }

        return numLasers;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

