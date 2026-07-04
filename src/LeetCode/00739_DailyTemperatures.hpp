#pragma once
#include <vector>
#include <stack>
#include <utility>
#include <iterator>
#include <type_traits>

class Solution739 {
public:
  std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) const {
    const auto n = std::ssize(temperatures);

    // result[i] = number of days until a warmer temperature.
    // Default is 0, which is correct if no warmer day exists.
    auto result = std::vector<std::remove_cvref_t<decltype(temperatures)>::value_type>(n, 0);

    // Stack stores indices of days still waiting for a warmer day.
    // Invariant:
    // temperatures[st[0]], temperatures[st[1]], ... are decreasing from bottom to top.
    //
    // Example:
    // temps = [73, 74, 75, 71]
    // When we see 74, it pops 73 because 74 is the first warmer day for 73.
    std::stack<int> st;

    for (auto i = 0; i < n; ++i) {
      // Today is warmer than the unresolved day on top of the stack.
      // Therefore, today is the first warmer day for that previous index.
      while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
        const int previousIndex = st.top();
        st.pop();

        result[previousIndex] = i - previousIndex;
      }

      // Current day is unresolved until a warmer future day appears.
      st.push(i);
    }

    return result;
  }
};

/*
auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution739{}.dailyTemperatures({30,50,50,60});
    return 0;
}
*/
