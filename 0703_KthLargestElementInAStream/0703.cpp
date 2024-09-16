/*
The kth largest element in a stream, each time we add an element, we need to return the kth largest element.

Example: k = 3, nums = {4,5,8,2}, let's sort it: {8,5,4,2}.
So the 1st largest is 8
       2nd largest is 5
       3rd largest is 4

Cases/examples:
1) If we add a new element equal to or greater than 4, then the 3rd largest has not changed.
2) If we add a new element less than 4, then we will push 4 out but need to insert this element into
   the list and sort it, then return the 3rd element.

   Note that we only need to maintain k elements, (8,5,4).

   Since we want the smallest element in the number of elements we maintain, we can do this using a min-heap.

It's quite counter intuitive, but check this out:

7
6
5 <- min heap element. If we want the 3rd largest element, then we can put the 3 largest elements in a min heap, and top of the min heap will be the 3rd largest element.
4
3 <- max heap element. If we want the 3rd smallest element, we can put the 3 smallest element in a max heap. The top of the heap will be the max of these element but the 3rd smallest.
2
1

Let's code this up!!!

*/

#include <vector>
#include <queue>

class KthLargest {
public:
    KthLargest(int k, const std::vector<int>& nums): m_k{k}
    {
        for(const auto n : nums)
        {
            add(n);
        }
    }
    
    int add(int val)
    {
        if(m_minHeap.size() < m_k || val > m_minHeap.top())
        {
            m_minHeap.push(val);
            
            if(m_minHeap.size() > m_k) m_minHeap.pop();
        }

        return m_minHeap.top();
    }

    int m_k;

    std::priority_queue<int, std::vector<int>, std::greater<int>> m_minHeap{};
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

auto main(int argc, char* argv[]) -> int
{
    return 0;
}

