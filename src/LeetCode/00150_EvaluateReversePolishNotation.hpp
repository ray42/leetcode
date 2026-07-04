#pragma once

#include <stack>
#include <string>
#include <vector>

class Solution150 {
public:
  int evalRPN(const std::vector<std::string>& tokens) const {

    std::stack<int> st;

    // Helper: pop the top value from the stack.
    // Keeps operator logic short and avoids repeated pop boilerplate.
    auto pop = [&]() {
      auto x = st.top();
      st.pop();
      return x;
      };

    for (const auto& token : tokens) {
      if (token == "+" || token == "-" || token == "*" || token == "/") {
        // Important: stack pops operands in reverse order.
        // Example: ["4", "2", "-"]
        // right = 2, left = 4, so result is 4 - 2.
        auto right = pop();
        auto left = pop();

        if (token == "+") {
          st.push(left + right);
        }
        else if (token == "-") {
          st.push(left - right);
        }
        else if (token == "*") {
          st.push(left * right);
        }
        else {
          // C++ integer division truncates toward zero,
          // matching the LeetCode problem requirement.
          st.push(left / right);
        }
      }
      else {
        // Token is an integer, possibly negative, e.g. "-11".
        st.push(std::stoi(token));
      }
    }

    // Final stack contains the value of the whole expression.
    return st.top();
  }
};