/*
https://leetcode.com/problems/reverse-nodes-in-k-group/description/

Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. 
If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

Example 1:
Input: head = [|1,2|,|3,4|,|5|], k = 2
Output:       [|2,1|,|4,3|,|5|]

Only 1,2 and 3,4 are reverse. 5 isn't, but you can't really see that here.

Example 2:
Input: head = [1,2,3],[4,5], k = 3
Output:       [3,2,1],[4,5]

Easier to see that 4,5 are not reversed.

Example 3:
Input: head = [1],[2],[3],[4],[5], k = 1
Output:       [1],[2],[3],[4],[5]

Explanation: Reversing the group [1,2] results in [2,1], then we connect the groups.
             But reversing a single node, e.g. [5] is [5] (i.e. no change). Then we connect up
             the nodes, which will results in the original list, no change!

-------------------------

Solution:

Intuition: We clearly want to reverse the k-length sub-list. How do we identify this list? 
Suppose k = 3, then we want to reverse the portion identified between the two pointers below:

Input:  d->1->2->3->4->5...
        ^  |-----|  ^

Output: d->3->2->1->4->5...
        ^  |-----|  ^

Let's see how we can create this sublist of reverse. Start two pointers at d and step by k:
L        R
d->1->2->3->4->5...

Note: When ever we break a link, it is wise to store the pointer the link is pointing to in case we need it.
In this case, if we are to reverse 1->2->3, 

we know that we will break the connection 3->4, but we need to get to 4 again...

Also, we need the pointer to 1 since we know to reverse a linked list, 
we need to pass the head of the linked list to reverse, which in this case is 1, i.e. we want to reverse 1->2->3

SO, we need pointers:
L1 L2    R1 R2
d->1->2->3->4->5...

First, let's reverse the list denoted by the pointers [L2,...,R1], we can set
R2->next = null and pass the head (L2) to the reverse algorithm:
reverse(L2), where L2 is the head of 1->2->3->null.
This will return 3->2->1->null

Now we have
k = 3
L1        L2     R1 R2
d->(null<-1)<-2<-3  4
         |--------| this section has been reversed

d still points to 1, it's not pointing to null.

Now we need to connect the ends:
L1->next = R1
L2->next = R2

Now we have
k = 3
L1 R1    L2 R2
d->3->2->1->4

Now we shift L1 and R1 to L2 so that we can start the whole process again:
         L1
         R1
d->3->2->1->4->5->6->7

Shift R1 by 3 and create L2 and R2:
         L1 L2    R1 R2
d->3->2->1->4->5->6->7
Now we shift the sublist [R2,...,R1] = [4->5->6]
etc....
-------------------------
How do we move the pointers such that we don't do anything if we cannot move beyond k steps?
i.e. if k = 3 and we are at 
d->1->2->3->4-5->null
L1
then we know we can move 3 steps:
d->1->2->3->4-5->null
L1       R1

But if we are at 
d->1->2->3->4-5->null
         L1
then we need to know the condition to stop, break out of the algorithm, since if we do move R1 three steps, then we have
d->1->2->3->4-5->null
         L1       R1.

this means that we don't want while(R1), because when this loop breaks, R1 will be on null. So we want
while(R1->next)
  R1 = R1->next // step R1 by 1
  // if doing this operation causes us to step on the last node: 5->null, then the condition causes us to stop.

Okay, we also need to fit k in here. Let's do this:

auto kk = k
while(R1->next && kk > 0)
  R1 = R1->next

if(kk > 0) break // this means we still have some steps to do but we have reached the end of the list.

DONE! That's pretty much the algorithm!!!
*/



// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};



class Solution {
public:

using PtrListNode = ListNode *;

    ListNode* reverseKGroup(ListNode* head, int k)
    { 
        auto dummy = ListNode{0,head};
        auto l1 = &dummy;
        auto r1 = &dummy;
        while(true)
        {
            // reset k
            auto kk = k;
            // Move r1 by k
            while(r1->next && kk > 0)
            {
                r1 = r1->next;
                --kk;
            }

            // if kk > 0, it means r1->next is null (i.e. we have reach the last node in the list),
            // but we haven't moved the required number of steps. So, we break out since we don't want
            // to reverse the last bits.
            if(kk>0)
            {
                break;
            }
            
            // Now we have
            // k = 3
            // l1           r1
            // dummy->1->2->3->4
            
            
            // Set l2 and r2 to the left of l1 and r1, respectively.
            auto l2 = l1->next;
            auto r2 = r1->next;
            
            // Now we have
            // k = 3
            // l1     l2    r1 r2
            // dummy->1->2->3->4

            // Reverse between [l2,r1]
            r1->next = nullptr;
            r1 = reverse(l2);

            // Now we have
            // k = 3
            // l1           l2      r1 r2
            // dummy->(null<-1)<-2<-3  4
            //             |--------| this section has been reversed

            l1->next = r1;
            l2->next = r2;

            // Now we have
            // k = 3
            // l1     r1    l2 r2
            // dummy->3->2->1->4

            // Now move l1 and r1 to l2 to begin the next iteration
            l1 = l2;
            r1 = l2;
        }

        return dummy.next;
    }

    auto reverse(PtrListNode head) -> PtrListNode
    {
        auto prev = PtrListNode{nullptr};
        while(head)
        {
            auto next = head->next;

            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }
};

auto main(int argc, char * argv[]) -> int
{
    auto l5 = ListNode{5,nullptr};
    auto l4 = ListNode{4,&l5};
    auto l3 = ListNode{3,&l4};
    auto l2 = ListNode{2,&l3};
    auto l1 = ListNode{1,&l2};
    Solution{}.reverseKGroup(&l1,2);
    return 0;
}


