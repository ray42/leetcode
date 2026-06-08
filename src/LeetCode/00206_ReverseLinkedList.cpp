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

// This is recursion but done in a slightly different order than the above (in the recursive step)
// and the one above took me a while to reason about, idk why.
class SolutionRec {
public:
using ListNodePtr = ListNode*;

    ListNode* reverseList(ListNode* head)
    {
        // We know that we need to point the current to the previous.
        // The base case is still when current is nullptr.
        // We need to return the previous when we get to the base case because that will be the new head.
        auto prev = ListNodePtr{nullptr};
        return reverseList(prev, head);
    }

    ListNodePtr reverseList(ListNodePtr prev, ListNodePtr current)
    {
        if(current == nullptr)
        {
            return prev;
        }

        auto next = current->next;
        current->next = prev;
        return reverseList(current,next);
    }
};

///////////////////////////////////////////////////////////////
// Below are for practice, exactly the same as above.

// Do both iterative and recursive
class SolutionIter {
public:
using ListNodePr = ListNode*;

    ListNode* reverseList(ListNode* head)
    {
        auto prev = ListNodePr{nullptr};
        auto current = head;
        while(current)
        {
            auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};

class SolutionRec {
public:
using ListNodePtr = ListNode*;

    ListNode* reverseList(ListNode* head)
    {
        // We know that we need to point the current to the previous.
        // The base case is still when current is nullptr.
        // We need to return the previous when we get to the base case because that will be the new head.
        auto prev = ListNodePtr{nullptr};
        return reverseList(prev, head);
    }

    ListNodePtr reverseList(ListNodePtr prev, ListNodePtr current)
    {
        if(current == nullptr)
        {
            return prev;
        }

        auto next = current->next;
        current->next = prev;
        return reverseList(current,next);
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

