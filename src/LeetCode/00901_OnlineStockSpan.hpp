#pragma once

#include <stack>
#include <utility>
using namespace std;

class StockSpanner901 {
private:

  struct PriceSpan {
    int price{ 0 };
    int span{ 0 };
  };

  // Monotonic decreasing stack:
  // Each pair is {price, span}.
  // The stack only keeps prices that can block future spans.
  stack<PriceSpan> st;

public:
  StockSpanner901() = default;

  int next(int price) {
    // Today's price always counts itself.
    int span = 1;

    // If previous prices are <= today's price, they are included
    // in today's span. Their stored spans let us skip whole blocks.
    //
    // Example:
    // prices: 100, 80, 60, 70
    // When 70 arrives, it absorbs 60's span, but stops at 80.
    while (!st.empty() && st.top().price <= price) {
      span += st.top().span;
      st.pop();
    }

    // Push the compressed block for this price.
    // After popping <= prices, stack remains strictly decreasing.
    st.push({ price, span });

    return span;
  }
};