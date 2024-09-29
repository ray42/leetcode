
/*

################## NAIVE APPROACH

The naive approach is to maintain a sorted vector.

findMedian will return:

if vec is odd 0,1,2, n = 3, we return n/2 = element in position 1
if vec is even, 0,1,2,3, return average of (n/2)-1 and n/2 element.

Complexity:
addNum: nlog n time, O(1) space (no extra space needed except for the vector)

findMedian O(1) both time and space


#######################################

Optimised

Intuition:

Finding the median of
0,1,2,3,4,5 involves locating the middle value(s). So we actually do not care what the order of the other values are, we just want the middle values.
0,1,[2],[3],4,5

So, really, we can partition the vector in two:
[0,1,2],[3,4,5]

Put the LHS into a max heap and RHS into a min heap. So the top are the values we want!


findMedian:
if both are empty, return 0 // edge case: no element
if one is empty, return the non-empty one. // edge case: 1 element
if lhs.size() > rhs.size() return lhs.top()
if lhs.size() < rhs.size() return rhs.top()
if lhs.size == rhs.size() return the average

Time Complexity: O(1)

addNumber:
if num < rhs.top
    put num in lhs
else
    put in num rhs

if lhs.size = rhs.size + 2
    pop rhs and put it in lhs

if rhs.size = lhs.size + 2
    pop lhs and put it in rhs

*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <queue>

// This works, but time exceeded. Time to speed this up!!!
class MedianFinderNaive {
public:
    
    void addNum(int num) {
        m_nums.push_back(num);
        std::ranges::sort(m_nums);
    }
    
    double findMedian() {
        if(auto size = m_nums.size(); size % 2)
        {
            return m_nums[size/2];
        }
        else
        {
            return (m_nums[size/2-1] + m_nums[size/2])/2.0;
        }
        return 0;
    }

    std::vector<int> m_nums{};
};

class MedianFinderOptimised {
public:
    
    void addNum(int num)
    {
        if(!lhsMaxHeap.empty() && !rhsMinHeap.empty())
        {
            if(num < rhsMinHeap.top())
            {
                lhsMaxHeap.push(num);
            }
            else
            {
                rhsMinHeap.push(num);
            }
        }
        // Otherwise, one of them are empty, so we only test the non-empty one.
        else if(!lhsMaxHeap.empty())
        {
            if(num > lhsMaxHeap.top())
            {
                rhsMinHeap.push(num);
            }
            else
            {
                lhsMaxHeap.push(num);
            }
        }
        else  if(!rhsMinHeap.empty())
        {
            if(num < rhsMinHeap.top())
            {
                lhsMaxHeap.push(num);
            }
            else
            {
                rhsMinHeap.push(num);
            }
        }
        else
        {
            lhsMaxHeap.push(num);
        }

        if(lhsMaxHeap.size() == rhsMinHeap.size() + 2)
        {
            lhsMaxHeap.push(rhsMinHeap.top());
            rhsMinHeap.pop();
        }
        else if(rhsMinHeap.size() == lhsMaxHeap.size() +2)
        {
            rhsMinHeap.push(lhsMaxHeap.top());
            lhsMaxHeap.pop();
        }
    }
    
    double findMedian()
    {
        if(lhsMaxHeap.empty() || rhsMinHeap.empty())
        {
            return !lhsMaxHeap.empty() ? lhsMaxHeap.top() :
                   !rhsMinHeap.empty() ? rhsMinHeap.top() : 0;
        }
        if(lhsMaxHeap.size() == rhsMinHeap.size())
        {
            return (lhsMaxHeap.top() + rhsMinHeap.top())/2.0;
        }
        else if(lhsMaxHeap.size() > rhsMinHeap.size())
        {
            return lhsMaxHeap.top();
        }
        else
        {
            return rhsMinHeap.top();
        }
        return 0;
    }

    std::priority_queue<int, std::vector<int>, std::less<int>> lhsMaxHeap{};
    std::priority_queue<int, std::vector<int>, std::greater<int>> rhsMinHeap{};
    
};


/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

auto main(int argc, char* argv[]) -> int
{
    auto rr = MedianFinderOptimised{};

    rr.addNum(0);
    rr.addNum(0);
    auto i = rr.findMedian();
    rr.addNum(3);
    auto ii = rr.findMedian();
    return 0;
}
