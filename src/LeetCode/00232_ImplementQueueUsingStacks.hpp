#pragma once

#include <stack>

using namespace std;

class MyQueue {
private:
  // New elements are always pushed here.
  //
  // Example after:
  //   push(1), push(2), push(3)
  //
  // in stack top -> 3
  //                 2
  //                 1
  //
  // This is reverse of queue order, so we cannot pop directly from here.
  stack<int> in;

  // Elements ready to be popped/peeked in correct queue order.
  //
  // After moving all elements from `in` to `out`:
  //
  // out stack top -> 1   // queue front
  //                  2
  //                  3
  //
  // Now top of `out` is the oldest element, exactly what queue needs.
  stack<int> out;

  // Core trick:
  // Only transfer elements from `in` to `out` when `out` is empty.
  //
  // Why?
  // If `out` already has elements, its top is still the true queue front.
  // Moving more elements too early would break FIFO order.
  //
  // Example:
  //   push(1), push(2), pop()
  //
  // Transfer happens:
  //   in:  [1, 2]  ->  out: [2, 1], top is 1
  //   pop() removes 1
  //
  // Now suppose push(3):
  //   in has 3
  //   out still has 2
  //
  // Queue order should be: 2, then 3.
  // So we must NOT move 3 into out yet.
  // We wait until out becomes empty.
  void moveInToOutIfNeeded() {
    if (out.empty()) {
      while (!in.empty()) {
        out.push(in.top());
        in.pop();
      }
    }
  }

public:
  MyQueue() = default;

  // Queue push:
  // Always O(1).
  //
  // We do not try to maintain queue order immediately.
  // We defer the expensive reversing work until pop/peek actually needs it.
  void push(int x) {
    in.push(x);
  }

  // Queue pop:
  // Remove the oldest element.
  //
  // If `out` has elements, its top is already the queue front.
  // If `out` is empty, transfer everything from `in` to `out` first.
  //
  // Amortized O(1):
  // One call may move many elements, but each element is moved from
  // `in` to `out` at most once.
  int pop() {
    moveInToOutIfNeeded();

    int front = out.top();
    out.pop();

    return front;
  }

  // Queue peek:
  // Return the oldest element without removing it.
  //
  // Same logic as pop(), except we do not call out.pop().
  int peek() {
    moveInToOutIfNeeded();
    return out.top();
  }

  // Queue is empty only if both stacks are empty.
  //
  // Marked const because this function does not modify the queue.
  bool empty() const {
    return in.empty() && out.empty();
  }
};


/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */