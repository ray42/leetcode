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
            if(token == "+")
            {
                const auto n = stack.top();
                stack.pop();
                const auto m = stack.top();
                stack.pop();
                stack.push(m+n);
            }
            else if(token == "-")
            {
                const auto n = stack.top();
                stack.pop();
                const auto m = stack.top();
                stack.pop();
                stack.push(m-n);
            }
            else if(token == "*")
            {
                const auto n = stack.top();
                stack.pop();
                const auto m = stack.top();
                stack.pop();
                stack.push(m*n);
            }
            else if(token == "/")
            {
                const auto n = stack.top();
                stack.pop();
                const auto m = stack.top();
                stack.pop();
                stack.push(m/n);
            }
            else
            {
                stack.push(std::stoi(token));
            }
        }
        return stack.top();
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto v = std::vector<std::string>{{"4","13","5","/","+"}};
    Solution{}.evalRPN(v);
    return 0;
}