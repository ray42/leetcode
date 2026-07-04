#pragma once


#include <stack>
#include <algorithm>

class MinStack {
private:
  std::stack<int> values; // Real stack values
  std::stack<int> mins;   // mins.top() = minimum of values at this depth

public:
  MinStack() = default;

  void push(int val) {
    values.push(val);

    // If this is the first value, it is the current minimum.
    // Otherwise, remember the smaller of:
    //   - the new value
    //   - the previous minimum
    //
    // Example:
    // push 5 -> mins: 5
    // push 2 -> mins: 5, 2
    // push 7 -> mins: 5, 2, 2
    mins.push(mins.empty() ? val : std::min(val, mins.top()));
  }

  void pop() {
    // Pop both stacks to keep depths aligned.
    values.pop();
    mins.pop();
  }

  int top() const {
    return values.top();
  }

  int getMin() const {
    // Because of the invariant, this is always O(1).
    return mins.top();
  }
};


/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
