/*
Example 1:

Input: nums = [1,3,4,2,2]
Output: 2

The problem statement has that len(nums) = n+1 and the values in nums are in the range [1,n].
This gives an indication that we might be able to do something with the indices and the value range.
Let's insert the indices:
 0 1 2 3 4
[1,3,4,2,2]

What can we do? Well, since there is at least 1 index for every value, we can turn this into a linked list,
where the index points to the value. E.g.
0 points to 1
1 points to 3
2 points to 4, etc...

If you draw this out, you will see that there is a cycle between nodes 2 and 4.
Also, if you draw this out, you will see that there are two nodes pointing to 2: 3 and 4.
Also, you will notice that 2 is the start of the cycle (hence it has two nodes pointing to it).

So, we can use linked list cycle detection, then we work out where the start of the linked list is with Floyd's algorithm, this
value is the value which will appear more than once!!!

How do we step?
The start of the linked list is where index 0 points to, so we can do:
auto slow = nums[0];
auto fast = nums[0];

slow = nums[slow]; // step once
fast = nums[nums[fast]]; step twice
*/


#include <vector>

class Solution {
public:
    int findDuplicate(const std::vector<int>& nums) 
    {
        auto slow = nums[0];
        auto fast = nums[0];
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        while(slow != fast);

        auto slow2 = nums[0];
        while(slow2 != slow)
        {
            slow2 = nums[slow2];
            slow = nums[slow];
        }
        return slow;
    }
};
