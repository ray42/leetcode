
#include <vector>
#include <queue>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
Imagine feeding the all the linked lists into a machine which, at each iteration, 
selects the smallest node and joins it into one linked list
*/
class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        auto comp = [](ListNode* lhs, ListNode* rhs){
            return lhs->val > rhs->val;
        };
        auto queue = std::priority_queue<std::remove_cvref_t<decltype(lists)>::value_type, std::remove_cvref_t<decltype(lists)>, decltype(comp)>{comp};

        auto dummy = ListNode{};

        // Insert all first nodes
        for(auto ptrListNode : lists)
        {
            if(ptrListNode) queue.push(ptrListNode);
        }

        auto current = &dummy;
        while(!queue.empty())
        {
            auto node = queue.top();
            queue.pop();
            if(node->next) queue.push(node->next);

            current->next = node;

            current = current->next;
        }
        return dummy.next;
    }
};