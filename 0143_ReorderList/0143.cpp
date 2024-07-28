
#include <vector>
#include <memory>



// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// For the trivial solution, we insert all the list node pointers into a vector, then we construct the re-ordered list
// by using two pointers starting from the beginning and end, working towards the middle.
// So at each iteration, we do:
// tail->next = p1;
// p1->next = p2;
// tail = tail->next->next // this is where we will attach the next p1
// Space: O(N)
// Time: O(N)
class SolutionTrivial {
public:
using PtrListNode = ListNode*;
    auto reorderList(ListNode* head) -> void
    {
        // Edge cases for 
        // [], [1], [1,2], only when we reach [1,2,3] is when re-ordering happens: [1,3,2]
        if(head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return;
        }

        auto nodePtrs = std::vector<PtrListNode>{};
        auto current = head;
        while(current)
        {
            nodePtrs.push_back(current);
            current = current->next;
        }

        // Construct the reordered linked list
        auto p1 = decltype(std::ssize(nodePtrs)){};
        auto p2 = std::ssize(nodePtrs) - 1;

        auto tmp = ListNode{};
        auto tail = &tmp; // this is a dummy node
        while(p1 <= p2)
        {
            // If p1 and p2 are pointing to the same node, only insert it once.
            if(p1 == p2)
            {
                tail->next = nodePtrs[p1];
                tail = tail->next;
                break;
            }
            
            tail->next = nodePtrs[p1];
            tail->next->next = nodePtrs[p2];

            tail = tail->next->next;

            ++p1;
            --p2;
        }

        tail->next = nullptr;
    }
};


// In this solution, we don't use any extra space.
// Let's visualise the input and output:
// 
// Odd number of nodes:
// Input:  0->1->2->3->4
// Output: 0->4->1->3->2
// 
// Even number of nodes:
// Input:  0->1->2->3->4->5
// Output: 0->5->1->4->2->3
// 
// We realise that if we can break the linked list in half, then reverse the second half, we can then easily create the final linked list.
//
// E.g. Odd: Input:      0->1->2 ->3->4
// half it:             [0->1->2] [3->4]
// Reverse second half: [0->1->2] [3<-4]
// Combine:              0->4->1->3->2
//
// E.g. Even: Input:      0->1->2->3->4->5
// half it:             [0->1->2] [3->4->5]
// Reverse second half: [0->1->2] [3<-4<-5]
// Combine:              0->5->1->4->2->3
// 
// Let's focus on halving it. To do it without extra storage, we will use a slow and fast pointer.
// However, the placement of the slow and fast pointers matter. What happens if they both start at the same element?
//
// This is the ending position:
// Odd:  1 2 3 4 5 6 7
//             p1    p2
// Since we want the LHS to have more nodes than the RHS, this means that p1 is on the LHS, right? Let's try with with even:
// 
// This is the ending position:
// Even: 1 2 3 4 5 6 7 8
//               p1    p2
// We said p1 is the end of the LHS, right? This would lead to this splitting: [1 2 3 4 5] [6 7 8] - which is clearly wrong.
// 
// Through trial and error, if we start the p1 at 1 and p2 at 2, then it works:
//
// This is the ending position:
// Odd:  1 2 3 4 5 6 7
//             p1    p2
// Partition: [1 2 3 4] [5 6 7]
//
// This is the ending position:
// Even: 1 2 3 4 5 6 7 8
//             p1      p2
// Partition: [1 2 3 4] [5 6 7 8]
// 
// Let's code this up.
class SolutionOptimisedSpace {
public:
using PtrListNode = ListNode*;
    auto reorderList(ListNode* head) -> void
    {
        // Edge cases for 
        // [], [1], [1,2], only when we reach [1,2,3] is when re-ordering happens: [1,3,2]
        if(head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return;
        }

        // 1) Split the linked list,
        // 2) Reverse right half
        // 3) Combine
        auto slow = head;
        auto fast = head->next;
        while(true)
        {
            // Advance slow by 1
            slow = slow->next;

            // Try to advance fast by 2, break if we cannot.
            // We know that slow->next is not null since we have check that in the previous iteration
            if(fast->next->next == nullptr)
            {
                // This means we can only advance fast by 1, not 2, so we break
                break;
            }

            fast = fast->next->next;

            if(fast->next == nullptr)
            {
                // fast has reached the end of the list, so break
                break;
            }
        }

        // Now we reverse the 2nd half of the list, which starts at slow->next
        auto rhsCurrent = slow->next;
        
        auto prev = PtrListNode{nullptr};
        while(rhsCurrent)
        {
            auto next = rhsCurrent->next;
            rhsCurrent->next = prev;
            prev = rhsCurrent;
            rhsCurrent = next;
        }

        // Now combine these two!
        auto rhsHead = prev;
        auto lhsHead = head;
        
        //auto tmp = ListNode{};
        //auto prev = &tmp;
        //while(lhsHead || rhsHead)
        //{
        //    prev->next = lhsHead;
        //    lhsHead->next = rhsHead;
        //}

        
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}

