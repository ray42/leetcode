#include <memory>
#include <unordered_set>



struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) 
    {
        auto dupes = std::unordered_set<decltype(head)>{};
        while(head)
        {
            if(const auto& [it, isInserted] = dupes.emplace(head);
               !isInserted)
            {
                return true;
            }
            head = head->next;
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

    auto ii = Solution{}.hasCycle(l0.get());
    auto rew = 42;
    return 0;
}

