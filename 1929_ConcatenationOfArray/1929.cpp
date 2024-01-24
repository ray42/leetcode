#include <vector>
#include <algorithm>
#include <iterator>

class Solution {
public:
    auto getConcatenation(std::vector<int>& nums) -> std::vector<int>
    {
        const auto oldSize = nums.size();
        nums.reserve(2*oldSize);
        std::copy_n(nums.begin(), oldSize, std::back_inserter(nums));
        return nums;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
