//#include <bits/stdc++.h> - doesn't work on windows :(
#include <string>
#include <cctype>
#include <algorithm>
#include <ranges>



class Solution 
{
public:
    bool isPalindrome(std::string& s) 
    {
        //// Remove non characters
        //std::erase_if(s,[](char c)
        //{
        //    auto test = !(('A' < c && c < 'Z') || ('a' < c && c < 'z'));
        //    return !(('A' < c && c < 'Z') || ('a' < c && c < 'z'));
        //});

        // Remove non characters
        std::erase_if(s,[](char c)
        {
            //auto test = !(('A' < c && c < 'Z') || ('a' < c && c < 'z'));
            //return !(('A' < c && c < 'Z') || ('a' < c && c < 'z'));
            return !std::isalnum(c);
        });

        //std::transform(s.begin(), s.end(), s.begin(),
        //[](unsigned char c)
        //{
        //    return std::toupper(c);
        //});

        // Now check for palindrome
        auto L = static_cast<int>(0);
        auto R = static_cast<int>(s.size() - 1);
        while( L < R)
        {
            if(std::toupper(s[L]) != std::toupper(s[R]))
            {
                return false;
            }
            ++L;
            --R;
        }

        return true;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto ssss = std::string{"race a car"};
    auto sss = Solution{}.isPalindrome(ssss);
    auto iii = 42;
    return 0;
}


