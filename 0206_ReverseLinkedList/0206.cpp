/*
Easy: https://leetcode.com/problems/reverse-linked-list/description/

1,2,3
val=1,next=2
val=2,next=3
val=3,next=null

val1, next=null

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
    auto reverseList(ListNode* head) -> ListNode*
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

auto main(int argc, char* argv[])->int
{
    auto l1 = ListNode{1};
    auto l2 = ListNode{2};
    auto l3 = ListNode{3};
    l1.next = &l2;
    l2.next = &l3;
    Solution{}.reverseList(&l1);
    auto iii = 42;
    return 0;
}

