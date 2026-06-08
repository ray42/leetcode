


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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        auto dummy = ListNode{};
        auto prev = &dummy;

        auto carry = 0;
        // "carry != 0" is to handle cases where l1 and l2 ends but we still have a carry over so we need to add it on at the end.
        // E.g. l1 = [9,9,9,9,9,9,9]
        // l2 = [9,9,9,9]
        while(l1 || l2 || carry != 0)
        {
            auto sum = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);

            auto node = new ListNode{sum %10, nullptr};
            prev->next = node;
            carry = sum/10;

            if(l1)
            {
                l1 = l1->next;
            }
            if(l2)
            {
                l2 = l2->next;
            }
            prev = prev->next;
        }
        return dummy.next;
    }
};

