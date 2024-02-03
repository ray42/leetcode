/*
Easy: https://leetcode.com/problems/reverse-linked-list/description/

Visualising the input and output:

Input:
1,2,3
val=1,next=2
val=2,next=3
val=3,next=null

Output:
3,2,1
val=3,next=2
val=2,next=1,
val=1,next=null
*/
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    using PtrListNode = ListNode *;
    auto reverseList(ListNode* head) -> PtrListNode
    {
        auto prev = PtrListNode{nullptr};
        auto current = head;
        while(current != nullptr)
        {
            auto currentNext = current->next;
            current->next = prev;
            prev = current;
            current = currentNext;
        }
        return prev;
    }
};


/*
Visualising the input and output:

Input:
1,2,3
val=1,next=2
val=2,next=3
val=3,next=null

Output:
3,2,1
val=3,next=2
val=2,next=1,
val=1,next=null
*/
// Recursive solution
class SolutionRecursion
{
public:
    using PtrListNode = ListNode *;
    auto reverseList(ListNode* head) -> PtrListNode
    {
        if(!head)
        {
            return head;
        }

        return reverseList(nullptr, head);
    }

private:

    auto reverseList(PtrListNode prev, PtrListNode current) -> PtrListNode
    {
        if(current == nullptr)
        {
            // prev is the new head
            return prev;
        }

        auto head = reverseList(current, current->next);
        current->next = prev;

        return head;
    }
};


auto main(int argc, char* argv[])->int
{
    auto l1 = ListNode{1};
    auto l2 = ListNode{2};
    auto l3 = ListNode{3};
    l1.next = &l2;
    l2.next = &l3;
    SolutionRecursion{}.reverseList(&l1);
    auto iii = 42;
    return 0;
}

