#include <vector>
#include <stack>
#include <utility>

// The one below this is the brute force solution which exceed the time limit.
// So, this solution uses a monotonic stack - it's much quicker.
class Solution {
public:

    auto dailyTemperatures(const std::vector<int>& temperatures) -> std::vector<int>
    {
        const auto numTemp = temperatures.size();
        auto result = std::vector<int>(numTemp);

        // Recall that, for a monotonic decreasing stack, for an element x
        // if x is popped off by an element y, then y is the greater element to the right.
        // as x goes in, if x is at the bottom of the stack, then it has no greater element to the left
        //  otherwise, the element greater to the left is the one below x as x goes in.

        // So we want to find greater elements to the right, let's create a monotonic stack, and each time
        // an element y pops off an element x, we know that y is the next greatest element to the right
        // and so we store result[x_i] = y_i - x_i, where x_i and y_i are the indices of x and y.
        auto stack = std::stack<std::pair<int,int>>{};

        for(auto i = 0; i < numTemp; ++i)
        {
            // The < is important here.
            // Initially, I did <=, which will make our stack strictly monotonically decreasing, 
            // since element x will pop element y if they are equal.
            // e.g. 5,4,3,3,2,1 -> 5,4,3,2,1 because the second 3 will pop the first 3.
            // However, in the context of this program, this is the wrong logic, since it implies that
            // the element to the right greater than the first 3 is the second 3 because 3 popped 3.
            // So using < will not give us a strictly decreasing stack, but it makes this program work.
            // in fact, I'm sure the stack doesn't need to be strictly decreasing, maybe I'm just making this up...
            while(!stack.empty() && stack.top().first < temperatures[i])
            {
                const auto& [val, index] = stack.top();
                result[index] = i - index;

                stack.pop();
            }

            stack.push({temperatures[i],i});
        }

        
        return result;
    }
};

// N^2 solution, this exceeds time limit
// I'll use a monotonic stack, see above
class SolutionNaiveTimeLimitExceeded {
public:

    auto dailyTemperatures(const std::vector<int>& temperatures) -> std::vector<int>
    {
        const auto numTemp = temperatures.size();
        auto result = std::vector<int>(numTemp);

        // Naive way of doing it
        for(auto i = 0; i < numTemp; ++i)
        {
            const auto& tempi = temperatures[i];
            for(auto j = i+1; j < numTemp; ++j)
            {
                if(temperatures[j] > tempi)
                {
                    result[i] = j-i;
                    break;
                }
            }
        }
        return result;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.dailyTemperatures({30,50,50,60});
    return 0;
}
