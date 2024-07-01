
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

/*
To get intuition, draw a graph of the position on y axis and time on bottom axis.
E.g. Let pos = [0, 2, 4], speed = [0.5, 1, 0.5]

  p
  |   _/      _/
  | _/      _/
  |/ /    _/
  | /   _/
  |/  _/
  | _/
  |/
  --------------- t

What can we deduce from the the above diagram?

1) Only lower position can form a fleet with higher positions.
2) if the current car does not form a fleet with the one above it, it means
      the current car is slower than all cars above it and now forms a new line where cars lower than it can form a fleet with it.
      Only if we find a car reaching the finish line at a later time than the current car that it becomes the new line which we compare to.

But how do we know if two cars will form a fleet? 
We know that p + s*t = target
where
p is the position
s is the speed
t is time
target is the target.

So if we have a car at p = 1, s = 2 and target is 10, what time would it reach the target?
Formula is t = (target - p)/s = 4.5

Say two cars C1 and C2, with C2 below C1. How do we know if C2 collides with C1?
Well, C2 wil collide with C1 if it reaches the target at a smaller time t than C1.

This gives rise to this algorithm:

1) Sort the cars by position, assuming the 
2) Insert the last element (greatest position) into the stack, this forms the first "line"
3) Loop from second to last car to the first:
        Calculate the time to reach the target for the top of stack and the current car.
        If the current car reaches the target before the top, then it must collide with top and we ignore it.
        Otherwise, if the current car reaches the target after the top, this means the current car forms a new line
            for other cars to collide into - so we push this current car to the stack.

return the size of the stack, this is the number of car fleets.
*/

class Solution
{
public:

    auto carFleet(int target, const std::vector<int>& position, const std::vector<int>& speed) -> int
    {
        // Need to sort by position
        auto posAndSpeeds = std::vector<std::pair<int,int>>{};
        for(auto i = 0; i < position.size(); ++i)
        {
            posAndSpeeds.emplace_back(position[i], speed[i]);
        }
        
        std::sort(posAndSpeeds.begin(), posAndSpeeds.end(), [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs){
            return lhs.first < rhs.first;
        });

        // Insert the last element to first
        auto carFleets = std::stack<std::pair<int,int>>{};
        carFleets.emplace(posAndSpeeds[posAndSpeeds.size() - 1]);

        // Now we go from second last right to left
        for(int i = posAndSpeeds.size()-2; i >= 0; --i)
        {
            // Check the top of the stack
            const auto& top = carFleets.top();

            // If the top reaches the target BEFORE the current car, then the current car can never
            // reach top to form a car fleet. The current car becomes the slowest car which other cars
            // can form a car fleet with.
            // If the current car can reach the finish line before the top, then it means they will become a 
            // car fleet and we do nothing with the current car.
            if((target - top.first)/static_cast<double>(top.second) < (target - posAndSpeeds[i].first)/static_cast<double>(posAndSpeeds[i].second))
            {
                carFleets.push(posAndSpeeds[i]);
            }
        }

        return carFleets.size();
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.carFleet(100, {0,2,4}, {4,2,1});
    auto ii = 9;
    return 0;
}

