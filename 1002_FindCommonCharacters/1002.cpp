#include <vector>
#include <string>
#include <array>

//#include <gtest/gtest.h>

class Solution {
public:
    std::vector<std::string> commonChars(const std::vector<std::string>& words)
    {
        auto freqs = std::array<int, 26>{};
        for(const auto& word : words)
        {
            for(const auto& c : word)
            {
                ++freqs[c - 'a'];
            }
        }
        auto result = std::vector<std::string>{};
        const auto numWords = words.size();
        for(const auto freq : freqs)
        {
            if(freq >= numWords)
            {
                result.push_back(std::string{static_cast<char>('a' + freq)});
            }
        }
        return result;
    }
};

//TEST(LeetCodeTest, firstTest)
//{
//    ASSERT_TRUE(true);
//}

//auto main(int argc, char* argv[]) -> int
//{
//    Solution{}.commonChars({"bella","label","roller"});
//    return 0;
//}

