#include <vector>

class Solution {
public:
    auto twoSum(const std::vector<int>& numbers, int target) -> std::vector<int> 
    {
        auto L = 0;
        auto R = static_cast<int>(numbers.size()-1);
        while(L < R)
        {
            const auto sum = numbers[L] + numbers[R];
            if(sum < target)
            {
                ++L;
                continue;
            }
            else if(sum > target)
            {
                --R;
                continue;
            }
            else
            {
                break;
            }
        }
        return{L+1, R+1};
    }
};

auto main(int argc, char* argv[]) -> int
{

}


