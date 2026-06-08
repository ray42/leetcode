
#include <vector>


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using LnPtr = ListNode*;
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2)
    {
        // Need to get the node before a and the node after b
        auto beforeA = list1;
        for(auto i = 0; i < a-1; ++i)
        {
            beforeA = beforeA->next;
        }
        auto afterB = beforeA;
        for(auto i = a-2; i <b; ++i)
        {
            afterB = afterB->next;
        }
        beforeA->next = list2;

        // Go to the end of list2
        while(beforeA->next)
        {
            beforeA = beforeA->next;
        }
        beforeA->next = afterB;

        return list1;
    }
};

auto getList(const std::vector<int>& vec)->LnPtr
{
    auto head = LnPtr{nullptr};
    auto prev = LnPtr{nullptr};
    for(const auto& val : vec)
    {
        auto node = new ListNode{val};
        if(prev != nullptr)
        {
            prev->next = node;
            
        }
        else
        {
            head = node;
        }
         prev = node;
    }
    return head;
}

auto main(int argc, char* argv[])-> int
{
    auto l1 = getList({0,1,2,3,4,5,6});
    auto a = 2;
    auto b = 5;
    auto l2 = getList({1000000,1000001,1000002,1000003,1000004});

    auto sss = Solution{}.mergeInBetween(l1,a,b,l2);


    auto iii = 42;

    return 0;
}

