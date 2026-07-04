#pragma once
#include <vector>
#include <stack>

using namespace std;

class Solution735 {
public:
  vector<int> asteroidCollision(const vector<int>& asteroids)const {
    vector<int> stack; // Survivors so far, in original left-to-right order.

    for (int right : asteroids) {
      bool rightAlive = true;

      // Collision is only possible when:
      //   stack.back() > 0  means previous asteroid moves right
      //   a < 0             means incoming asteroid moves left
      //
      // Example:
      //   [5, 10, -5]
      //        10 ->  <- -5 collide
      //
      // But these do NOT collide:
      //   [-5, 10]   moving away from each other
      //   [5, 10]    same direction
      //   [-5, -10]  same direction
      while (rightAlive && right < 0 && !stack.empty() && stack.back() > 0) {
        const auto left = stack.back();

        if (left < -right) {
          // Top asteroid is smaller, so it explodes.
          //
          // Example:
          //   stack = [4], a = -7
          //   4 explodes, -7 may continue left into earlier asteroids.
          stack.pop_back();
        }
        else if (left == -right) {
          // Equal sizes: both explode.
          //
          // Example:
          //   stack = [8], a = -8
          //   both disappear.
          stack.pop_back();
          rightAlive = false;
        }
        else {
          // Top asteroid is bigger, incoming asteroid explodes.
          //
          // Example:
          //   stack = [10], a = -3
          //   -3 disappears, 10 survives.
          rightAlive = false;
        }
      }

      // If a was not destroyed, it becomes a survivor.
      //
      // This includes:
      //   positive asteroids, e.g. 5
      //   negative asteroids with no right-moving asteroid before them, e.g. [-5]
      //   negative asteroids that destroyed all smaller positives before them.
      if (rightAlive) {
        stack.push_back(right);
      }
    }
    return stack;
  }
};
