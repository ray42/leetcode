/*
https://leetcode.com/problems/merge-two-sorted-lists/
*/

#include <memory>

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

    auto mergeTwoLists(ListNode* list1, ListNode* list2) -> ListNode*
    {
        if(list1 == nullptr)
        {
            return list2;
        }
        if(list2 == nullptr)
        {
            return list1;
        }

        // Now determine the "current" and store the head to be returned.
        auto head = PtrListNode{nullptr};
        auto current = PtrListNode{nullptr};

        auto p1 = PtrListNode{nullptr}; // pointer to the next node to be considered in list1
        auto p2 = PtrListNode{nullptr}; // pointer to the next node to be considered in list1
        if(list1->val < list2->val)
        {
            current = list1;
            head = list1;
            p1 = current->next;
            p2 = list2;
        }
        else
        {
            current = list2;
            head = list2;
            p1 = list1;
            p2 = current->next;
        }

        while(p1 != nullptr  && p2 != nullptr)
        {
            if(p1->val < p2->val)
            {
                current->next = p1;
                current = p1;
                p1 = current->next;
            }
            else
            {
                current->next = p2;
                current = p2;
                p2 = current->next;
            }
        }

        if(p1 != nullptr)
        {
            current->next = p1;
        }
        if(p2 != nullptr)
        {
            current->next = p2;
        }

        return head;
    }
};

class SolutionRecursiveVersion {
public:
    using PtrListNode = ListNode *;

    auto mergeTwoLists(PtrListNode list1, PtrListNode list2) -> PtrListNode
    {
        if(list1 == nullptr)
        {
            return list2;
        }
        if(list2 == nullptr)
        {
            return list1;
        }

        // Now determine the "current" and store the head to be returned.
        auto head = PtrListNode{nullptr};
        auto current = PtrListNode{nullptr};

        auto p1 = PtrListNode{nullptr}; // pointer to the next node to be considered in list1
        auto p2 = PtrListNode{nullptr}; // pointer to the next node to be considered in list1
        if(list1->val < list2->val)
        {
            current = list1;
            head = list1;
            p1 = current->next;
            p2 = list2;
        }
        else
        {
            current = list2;
            head = list2;
            p1 = list1;
            p2 = current->next;
        }

        mergeTwoLists(current, p1, p2);

        return head;
    }
private:
    auto mergeTwoLists(PtrListNode current, PtrListNode p1, PtrListNode p2) -> void
    {
        if(p1 == nullptr || p2 == nullptr)
        {
            if(p1 != nullptr)
            {
                current->next = p1;
            }
            else // Otherwise, p2 is either not null or is null, either way, we can just set next to p2
            {
                current->next = p2;
            }
            return;
        }

        if(p1->val < p2->val)
        {
            current->next = p1;
            current = p1;
            p1 = current->next;
        }
        else
        {
            current->next = p2;
            current = p2;
            p2 = current->next;
        }

        mergeTwoLists(current, p1, p2);
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}
