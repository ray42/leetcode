/*
Easy: https://leetcode.com/problems/valid-parentheses/
*/
#include <cassert>
#include <string>
#include <vector>


class Solution {
public:
    auto isValid(const std::string& s) -> bool
    {
        auto stack = std::vector<char>{};

        for(const auto c : s)
        {
            switch(c)
            {
                case '(':
                stack.push_back('(');
                break;
                case '{':
                stack.push_back('{');
                break;
                case '[':
                stack.push_back('[');
                break;
                case ')':
                {
                    if(stack.empty() || stack.back() != '(') return false;
                    stack.pop_back();
                }
                break;
                case ']':
                {
                    if(stack.empty() || stack.back() != '[') return false;
                    stack.pop_back();
                }
                break;
                case '}':
                {
                    if(stack.empty() || stack.back() != '{') return false;
                    stack.pop_back();
                }
                break;
                default:
                    assert(0);
                break;
            }
        }

        // If it's not empty, then we have an unmatched parenthesis.
        return stack.empty();
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto sol = Solution{}.isValid("]");
    return 0;
}
