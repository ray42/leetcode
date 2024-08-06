/*
Look at "Fast and Slow Pointers" on obsidian
*/

#include <memory>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class SolutionHash 
{
public:
    bool hasCycle(ListNode *head) 
    {
        auto setListNode = std::unordered_set<ListNode*>{};

        while(head)
        {
            if(const auto& [it, inserted] = setListNode.insert(head);
               !inserted)
            {
                return true;
            }
            head = head->next;
        }
        return false;
    }
};

class SolutionTwoPointer 
{
public:
    bool hasCycle(ListNode *head)
    {
        if(!head) return false;

        auto slow = head;
        auto fast = head;
        while(fast && fast->next) // because we need fast and fast->next to exist to get fast->next->next
        {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)
            {
                return true;
            }
        }
        return false;
    }
};

auto main(int argc, char* argv[]) -> int
{
    // [3,2,0,-4]
    // 1
    auto l0 = std::make_shared<ListNode>(3);
    auto l1 = std::make_shared<ListNode>(2);
    auto l2 = std::make_shared<ListNode>(0);
    auto l3 = std::make_shared<ListNode>(-4);

    l0->next = l1.get();
    l1->next = l2.get();
    l2->next = l3.get();
    l3->next = l1.get(); // Loop

    //auto ii = Solution{}.hasCycle(l0.get());
    auto rew = 42;
    return 0;
}

