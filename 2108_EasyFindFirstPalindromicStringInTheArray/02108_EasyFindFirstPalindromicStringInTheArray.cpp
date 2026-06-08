
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    auto firstPalindrome(const std::vector<std::string>& words) -> std::string
    {
        auto it =  std::ranges::find_if(words, [](const std::string& word){
            // Check if the string is palindrome
            const auto wordSize = word.size();
            for(auto i = 0; i < wordSize/2; ++i)
            {
                if(word[i] != word[wordSize - i - 1])
                    return false;
            }
            return true;
        });

        return it == words.end() ? "" : *it;
    }
};

auto main(int argc, char* argv[])->int
{
    return 0;
}
