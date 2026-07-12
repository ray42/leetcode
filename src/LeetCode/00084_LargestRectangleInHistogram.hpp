#pragma once

#include <algorithm>
#include <iterator>
#include <stack>
#include <utility>
#include <vector>

// This is the more intuitive solution given to me by
// m365 chat GPT5.6
class Solution84_intuitiveSolution
{
public:
  int largestRectangleArea(vector<int>& heights) const {
    stack<int> st;       // Indices of non-decreasing bar heights.
    long long best = 0;
    auto n = std::ssize(heights);

    // Process one extra virtual bar of height 0.
    // Example: [2, 3] never encounters a shorter real bar,
    // so the virtual 0 forces both remaining bars to be evaluated.
    for (int i = 0; i <= n; ++i) {
      // At i == n, use an artificial height of 0 to flush
      // all remaining columns from the stack.
      int currentHeight = (i == n) ? 0 : heights[i];

      // A shorter bar ends every taller rectangle on the stack.
      //
      //               0  1  2  3
      // Example: for [1, 5, 6, 2], when i = 3:
      // - Pop height 6: it can only span index 2.
      // - Pop height 5: it can span indices 1..2.
      while (!st.empty() && heights[st.top()] > currentHeight) {
        int mid = st.top();
        st.pop();

        // i is the first strictly shorter bar on the right.
        //
        // After popping, st.top() is the nearest remaining bar on the left
        // whose height is less than or equal to heights[mid].
        //
        // If it has equal height, the current popped bar gets a narrower
        // rectangle. That equal-height bar will be popped later and will
        // represent the wider rectangle.
        //
        // If the stack is empty, the rectangle extends from index 0
        // through index i - 1, so its width is i.
        int width = st.empty() ? i : i - st.top() - 1;

        long long area =
          static_cast<long long>(heights[mid]) * width;
        best = max(best, area);
      }

      // Do not push the virtual sentinel index because heights[n]
      // does not exist. All real bars have already been flushed.
      if (i < n) {
        st.push(i);
      }
    }

    return static_cast<int>(best);
  }
};

class Solution84 {
public:
  struct Column
  {
    int val;
    int index;
    int left;
    int right;

    constexpr auto operator<=>(const Column&) const = default;
  };
  auto largestRectangleArea(const std::vector<int>& heights) -> int
  {
    // Use a monotonic increasing stack to track the next smallest element to the left
    // and to the right.
    // Recall that in a monotonic increasing stack, for an element x_i:
    // 1) To get the next smaller element to the LEFT of x_i, 
    //    it's the element under x_i as x_i goes in.
    //    If there is no element under x_i as x_i goes in, 
    //    it means there are no elements smaller than x_i to the left of it
    // 2) To get the next smaller element to the RIGHT of x_i, 
    //    it's the element x_j which pops x_i as x_j goes in.
    //    If at the end of the loop, nothing pops off x_i, 
    //    then there is no smaller element to the RIGHT of x_i
    auto stack = std::stack<Column>{};
    auto largestArea = 0;
    const auto& heightSize = heights.size();
    for (auto i = 0; i < heightSize; ++i)
    {
      // Find the correct place to put the next element.
      // This is a monotonic increasing stack, 
      // so we want the top to be less than the current element.
      while (!stack.empty() && stack.top().val >= heights[i])
      {
        // Since this has been put in (so we have the left) and now it's 
        // being popped off, we have the left and right to calculate the area.
        const auto& colPopped = stack.top();
        const auto right = i;
        const auto width = right - colPopped.left - 1;
        const auto newArea = colPopped.val * width;
        largestArea = std::max(largestArea, newArea);

        stack.pop();
      }

      // Now we can put in the stack, but before that, we need to get the left.
      auto newCol = Column{};
      newCol.val = heights[i];
      newCol.index = i;
      newCol.left = stack.empty() ? -1 : stack.top().index;
      stack.push(newCol);
    }

    // What about the elements still on the stack? This means 
    // they have no smaller to the right, the right will be heights.size()
    while (!stack.empty())
    {
      const auto& colPopped = stack.top();
      const auto newArea = static_cast<int>(colPopped.val * (heightSize - colPopped.left - 1));
      largestArea = std::max(largestArea, newArea);

      stack.pop();
    }

    return largestArea;
  }
};