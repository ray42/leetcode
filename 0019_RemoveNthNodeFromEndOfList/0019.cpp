#include <memory>

// Definition for singly-linked list.
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// We do two solutions: (1) Two pass and (2) two pointers.


// Two pass: let n
// head =  [1,2,3,4,5], n = 2
// Output: [1,2,3,  5]
//
// 1) With the help of a dummyHead, count the number of nodes:
// dummyHead->1->2->3->4->5->null
//  Staring at dummyHead, we can go until current->next is null, incrementing a counter.
//
// 2) The node previous to the node we want to remove will be "nnode - n", in the example: 5 - 2 = 3,
// dummyHead->1->2->3->4->5->null
//                
// Staring at dummyHead, we step nnode-n = 3 times.
//
// 3) Perform the removal:
//    current->next = current->next->next
//
// Edge cases:
// The above approach works for removing the first and last node (corresponding to n = 5 and n = 1 in the above example)
class SolutionTwoPass {
public:
    using PtrListNode = ListNode*;
    auto removeNthFromEnd(ListNode* head, int n) -> ListNode*
    {
        // With the help of a dummyHead, count the number of nodes
        auto dummyHead = ListNode{0,head};
        auto current = &dummyHead;
        auto nnodes = int{0};
        while(current->next)
        {
            ++nnodes;
            current = current->next;
        }

        // Move to the node previous to the one we want to remove.
        auto prevNodeNum = nnodes - n;
        current = &dummyHead;
        while(prevNodeNum > 0)
        {
            current = current->next;
            --prevNodeNum;
        }

        // Do the deletion
        current->next = current->next->next;

        return dummyHead.next;
    }
};

// One pass, two pointer solution.
// Input:  dH->1->2->3->4->5->null n = 2
// Output: dH->1->2->3  -> 5->null
//
// 1)
// Use two pointers, start at a dummyHead and increment the second pointer by n.
// dH->1->2->3->4->5->null
// ^      ^ (increment pointer by 2)
// 
// 2)
// Now we move them both until the incremented pointer's next is null. 
// The first pointer will be at the previous node to the one which we want to remove:
// 
// dH->1->2->3->4->5->null
//           ^     ^
// 
// 3) Now perform the removal for the pointer at 3.
// current->next = current->next->next
class SolutionTwoPointer {
public:
using PtrListNode = ListNode*;
    auto removeNthFromEnd(ListNode* head, int n) -> ListNode*
    {
        auto dummy = ListNode{0,head};

        auto first = &dummy;
        auto second = &dummy;
        // 1) Move the second pointer by n
        while(n>0)
        {
            second = second->next;
            --n;
        }

        // 2) Move both pointers until the second pointer reaches the end of the list
        while(second->next)
        {
            first = first->next;
            second = second->next;
        }

        // 3) Remove the node after first
        first->next = first->next->next;

        // Return the head. Note that the original head could have been removed, so we need to return
        // dummy.next
        return dummy.next;
    }
};





auto main(int argc, char* argv[]) -> int
{
    auto n5 = std::make_shared<ListNode>(5, nullptr);
    auto n4 = std::make_shared<ListNode>(4, n5.get());
    auto n3 = std::make_shared<ListNode>(3, n4.get());
    auto n2 = std::make_shared<ListNode>(2, n3.get());
    auto n1 = std::make_shared<ListNode>(1, n2.get());

    auto ii = SolutionTwoPointer{}.removeNthFromEnd(n1.get(),2);

    return 0;
}

