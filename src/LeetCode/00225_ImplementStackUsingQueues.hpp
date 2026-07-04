#pragma once


#include <queue>
#include <iterator>

class MyStack {
private:
  std::queue<int> q;

public:
  MyStack() = default;

  void push(int x) {
    q.push(x);

    // If we push an element to the queue, 
    // we need to rotate the queue to make the 
    // last pushed element to be at the front of the queue.
    // [3, 2, 1] -> push(4) -> [3, 2, 1, 4] -> [4, 3, 2, 1]
    const auto rotations = std::ssize(q) - 1;
    for (int i = 0; i < rotations; ++i) {
      q.push(q.front());
      q.pop();
    }
  }

  int pop() {
    int result = q.front();
    q.pop();
    return result;
  }

  int top() const {
    return q.front();
  }

  bool empty() const {
    return q.empty();
  }
};


/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */