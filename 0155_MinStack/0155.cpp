/*
Medium : https://leetcode.com/problems/min-stack/description/

The "trick" is to keep track of the minimal element.
We do this with a second stack, which keeps track of the minimum element SO FAR.

To see this, see the following example:
arr    = [9,11,12,8,99,5,9,8,1,20]
minArr = [9,9, 9, 8,8, 5,5,5,1,1]

Going from left to right, we see:
Push 9,  smallest element so far is 9.
Push 11, smallest element so far is still 9.
Push 12, smallest element so far is still 9.
Push 8,  smallest element so far is 8.

So when we want to get the smallest element, we can just peek at minArr.
When we pop, we pop both arr and minArr to keep them synchronised.
*/

#include <stack>

class MinStack 
{
public:

    MinStack() 
    {
        
    }
    
    auto push(int val) -> void
    {
        arr.push(val);
        minArr.push(
            minArr.empty()? val : 
            minArr.top() < val ? minArr.top() : val
        );
    }
    
    auto pop() -> void
    {
        arr.pop();
        minArr.pop();
    }
    
    auto top() -> int
    {
        return arr.top();
    }
    
    auto getMin() -> int
    {
        return minArr.top();
    }

private:

    std::stack<int> arr{};
    std::stack<int> minArr{};
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

auto main(int argc, char* argv[])-> int
{
    return 0;
}
