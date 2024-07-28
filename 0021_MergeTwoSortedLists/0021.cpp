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

class SolutionIter {
public:
using PtrListNode = ListNode *;

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        auto dummyHead = std::make_unique<ListNode>();
        auto current = dummyHead.get();
        
        while(list1 && list2)
        {
            if(list1->val < list2->val)
            {
                current->next = list1;
                list1 = list1->next;
            }
            else
            {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }

        if(list1)
        {
            current->next = list1;
        }
        if(list2)
        {
            current->next = list2;
        }

        return dummyHead->next;
    }
};

class SolutionRecursiveVersion {
public:
    using PtrListNode = ListNode *;

    auto mergeTwoLists(PtrListNode list1, PtrListNode list2) -> PtrListNode
    {
        return {};
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
