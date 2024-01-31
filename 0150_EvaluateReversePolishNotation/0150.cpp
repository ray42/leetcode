/*
https://leetcode.com/problems/evaluate-reverse-polish-notation/description/
this gives a runtime error. Must re-visit and do.
*/

#include <vector>
#include <string>
#include <stack>

class Solution {
public:
    auto evalRPN(const std::vector<std::string>& tokens) -> int
    {
        auto stack = std::stack<int>{};
        for(const auto& token : tokens)
        {
            if(isNumber(token))
            {
                stack.push(std::stoi(token));
            }
            else if(token == "+")
            {
                auto i = stack.top();
                stack.pop();
                auto j = stack.top();
                stack.pop();
                stack.push(i+j);
            }
            else if(token == "/")
            {
                auto i = stack.top();
                stack.pop();
                auto j = stack.top();
                stack.pop();
                stack.push(i/j);
            }
            else if(token == "*")
            {
                auto i = stack.top();
                stack.pop();
                auto j = stack.top();
                stack.pop();
                stack.push(i*j);
            }
            else if(token == "-")
            {
                auto i = stack.top();
                stack.pop();
                auto j = stack.top();
                stack.pop();
                stack.push(i-j);
            }
        }
        return stack.top();
    }

    auto isNumber(const std::string& s) -> bool
    {
        return s.empty() && 
        std::find_if(s.begin(), s.end(), 
        [](unsigned char c){
            return !std::isdigit(c);
        }) == s.end();
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}