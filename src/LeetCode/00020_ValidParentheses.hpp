#pragma once

#include <string>
#include <stack>

// The key intuition for Valid Parentheses is :
// 
// Brackets must close in the reverse order that they were opened.
// That "reverse order" idea is exactly what a stack is good for.
// A stack is last in, first out.

class Solution20 {
public:
  bool isValid(const std::string& s) const {
    auto stack = std::stack<char>{};

    for (const auto& c : s)
    {
      if (c == '(' || c == '{' || c == '[')
      {
        stack.push(c);
      }
      else
      {
        // If the stack is empty, it means there 
        // is no matching opening bracket for the 
        // current closing bracket, so we return false.
        if (stack.empty()) return false;

        const auto top = stack.top();
        stack.pop();
        if (c == ')' && top != '(') return false;
        if (c == '}' && top != '{') return false;
        if (c == ']' && top != '[') return false;
      }
    }

    // If not empty, then we have unmatched opening 
    // brackets, so we return false.
    return stack.empty();
  }
};