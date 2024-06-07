
#include <vector>
#include <string>

class Solution {
public:
    auto generateParenthesis(const int n) -> std::vector<std::string>
    {
        auto ret = std::vector<std::string>{};
        for(auto i = 1; i <= n; ++i)
        {
            auto newRet = std::vector<std::string>{};
            // First we insert "()" where there is an open brace.
            for(const auto& v : ret)
            {
                // per token, there are i ways (the number of open )
                for(auto j = 0; j < i; ++j)
                {

                }
            }
        }
    }
};


auto main(int argc, char * argv[]) -> int
{
    return 0;
}

