
// https://medium.com/algorithms-digest/largest-rectangle-in-histogram-234004ecd15a


/*

*/

#include <vector>
#include <stack>
#include <utility>

class Solution {
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
        // 1) To get the next smaller element to the LEFT of x_i, it's the element under x_i as x_i goes in.
        //    If there is no element under x_i as x_i goes in, it means there are no elements smaller than x_i to the left of it
        // 2) To get the next smaller element to the RIGHT of x_i, it's the element x_j which pops x_i as x_j goes in.
        //    If at the end of the loop, nothing pops off x_i, then there is no smaller element to the RIGHT of x_j
        auto stack = std::stack<Column>{};
        auto largestArea = 0;
        const auto& heightSize = heights.size();
        for(auto i = 0; i < heightSize; ++i)
        {
            // Find the correct place to put the next element.
            // This is a monotonic increasing stack, so we want the top to be less than the current element.
            while(!stack.empty() && stack.top().val >= heights[i])
            {
                // Since this has been put in (so we have the left) and now it's being popped off, we have the left and right to calculate
                // the area.
                const auto& colPopped = stack.top();
                const auto newArea = colPopped.val * (i-colPopped.left - 1);
                largestArea = std::max(largestArea, newArea);

                stack.pop();
            }

            // Now we can put in the stack, but before that, we need to get the left.
            auto newCol = Column{};
            newCol.val = heights[i];
            newCol.index = i;
            newCol.left = stack.empty()? -1: stack.top().index; // Because if you draw out the histogram, this is the index where it's smaller than the current newCol
            stack.push(newCol);
        }

        // What about the elements still on the stack? This means they have no smaller to the right, the right will be heights.size()
        while(!stack.empty())
        {
                const auto& colPopped = stack.top();
                const auto newArea = static_cast<int>(colPopped.val * (heightSize - colPopped.left - 1));
                largestArea = std::max(largestArea, newArea);

                stack.pop();
        }

        return largestArea;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.largestRectangleArea({2,1,5,6,2,3});
    return 0;
}

