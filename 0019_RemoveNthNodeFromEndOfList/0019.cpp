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
// We go to the end to see how many nodes there are.
// Let sz be the number of nodes. Then we can do sz - n to get the prev node of the one we want to remove.
// E.g. 5-2 = 3, so we go to the third node, and set it's next pointer to point to the next next pointer.
// Edge cases: What happens at n=5 (remove the head) and n=1 (remove the last node)?
// if n = 5, then we have 5-5 = 0, in this case, we need to set the head to the head's next node.
// if n = 1, then we have 5-1 = 4, then we set the 4th node's next pointer to the next next pointer (which is null) - this is no different than the normal case.s
class Solution1 {
public:
    auto removeNthFromEnd(ListNode* head, int n) -> ListNode*
    {
        // Just in case we have a null head.
        if(!head) return head;

        // Count the number of nodes
        auto sz = 0;
        auto temp = head;
        do
        {
            ++sz;
            temp = temp->next;
        }
        while(temp);

        auto prevNodeIndex = sz - n;

        // This works for head = [1], n = 1, we return null in this case.
        if(prevNodeIndex == 0) return head->next;

        auto dummyNode = ListNode{0, head};
        auto ptrDummyNode = &dummyNode;

        // Now go to the previous node (to the one we want to remove) and remove it.
        while(prevNodeIndex > 0)
        {
            ptrDummyNode = ptrDummyNode->next;
            --prevNodeIndex;
        }

        ptrDummyNode->next = ptrDummyNode->next->next;
        
        return head;
    }
};

// One pass, two pointer solution.
// head =  [1,2,3,4,5]
// if n = 0, then prev = 5
// if n = 1, then prev = 4
// if n = 4, then prev = 1
// if n = 5, then prev = the node before 1 (this is a special case).
// Note that prev is n position away from the last node. So what we can do is maintain two pointers, n nodes apart.
// Then, once the fast pointer reaches the last node, we know that the slow pointer is at the correct prev position.
// 
// NOTE: We don't even need to do the special case if we return dummy.next, which is what I have done.
// How do we handle the special case?
// When placing the slow and fast pointers, we start a dummy node which points to the head.
// If n = 5, then we move the fast pointer 5 times to point to 5, then we can check it's next pointer, if it's nullptr, then we have reach the special case.
//     Then we simply return head->next
class Solution2 {
public:
    auto removeNthFromEnd(ListNode* head, int n) -> ListNode*
    {
        if(!head) return head;

        auto dummy = ListNode{0, head};
        auto fast = &dummy;
        auto slow = &dummy;
        while(n > 0)
        {
            fast = fast->next;
            --n;
        }

        // Start shifting both pointers until fast->next is nullptr
        while(fast->next)
        {
            slow = slow->next;
            fast = fast->next;
        }

        // Perform the removal
        slow->next = slow->next->next;

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

    auto ii = Solution2{}.removeNthFromEnd(n1.get(),2);

    return 0;
}

