/*
Medium Premium: https://www.lintcode.com/problem/659/

Description

Design an algorithm to encode a list of strings to a string. 
The encoded string is then sent over the network and is decoded back to the original list of strings.

Please implement encode and decode.

Example1

Input: ["lint","code","love","you"]
Output: ["lint","code","love","you"]
Explanation:
One possible encode method is: "lint:;code:;love:;you"

Example 2

Input: ["we", "say", ":", "yes"]
Output: ["we", "say", ":", "yes"]
Explanation:
One possible encode method is: "we:;say:;:::;yes"

RAYNOTES
We COULD use a delimiter, but what if the delimiter is a part of the input?
E.g. if we choose # as our delimeter, and if the input is:
Input: ["###we", "##say", "#:##", "###yes"], then our encoding will give us:
"###we###say##:######yes", which is impossible to decode. 

What we can do is encode the length of each word and use a special character, so
our delimeter is len(word)#, where len(word) is the length of the word.

E.g.
Input: ["we", "say", ":", "yes"]
Encoding: 2#we3#say1#:3#yes
*/

#include <string>
#include <vector>
#include <tuple>
#include <cctype>
#include <iostream>

class Solution {
public:
    /*
     * @param strs: a list of strings
     * @return: encodes a list of strings to a single string.
     */
    auto encode(const std::vector<std::string> &strs) -> std::string
    {
        auto encodedStrings = std::string{};
        for(const auto& str : strs)
        {
            encodedStrings += std::to_string(str.size()) + '#' + str;
        }
        return encodedStrings;
    }

    /*
     * @param str: A string
     * @return: decodes a single string to a list of strings
     */
    auto decode(const std::string &str) -> std::vector<std::string>
    {
        auto decodedStrings = std::vector<std::string>{};
        auto i = 0;
        while(i < str.size())
        {
            auto decodedString = std::string{};
            std::tie(decodedString,i) = extractString(str,i);

            decodedStrings.push_back(decodedString);
        }
        return decodedStrings;
    }

    auto extractString(const std::string& str, int i) -> std::tuple<std::string, int>
    {
        // Get the number
        auto j = i;
        while(j < str.size() && str[j] != '#') ++j;

        auto numberOfDigits = j-i;

        auto len = std::stoi(str.substr(i,numberOfDigits));

        // j is at the end of the number, which is the hash is
        // so we +1 to get to where the first letter is.
        auto decodedStr = std::string{};

        if(len > 0) decodedStr = str.substr(j + 1,len);
        
        return {decodedStr, j + 1 + len};
    }
};

auto print(const std::vector<std::string>& vecs) -> void
{
    for(const auto& str : vecs)
    {
        std::cout << str << ", ";
    }
}
auto main(int argc, char* argv[]) -> int
{
    //auto encoded = Solution{}.encode(std::vector<std::string>{"lint","code","love","you"}); // working
    //auto encoded = Solution{}.encode(std::vector<std::string>{"lint","code","","you"}); // working
    //auto encoded = Solution{}.encode(std::vector<std::string>{"lint","code","love",""}); // working
    //auto encoded = Solution{}.encode(std::vector<std::string>{""}); // working
    //auto encoded = Solution{}.encode(std::vector<std::string>{}); // working
    auto encoded = Solution{}.encode(std::vector<std::string>{"99lint","5435code","545l543o5ve","543y543ou"}); // working

    std::cout << encoded << '\n';
    auto decoded = Solution{}.decode(encoded);
    print(decoded);

    return 0;
}


