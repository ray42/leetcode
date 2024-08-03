
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

        // Need to do three things:
        // 1) Split the linked list,
        // 2) Reverse right half
        // 3) Combine
        


        // 1) Split the linked list,
        auto slow = head;
        auto fast = head->next;

        // How did we derive this condition? Let's check out where the fast pointer lands in both even and odd number cases:
        // 1->2->3->4
        //          ^ fast ends here
        //    ^ slow ends here
        // 1->2->3->4->5
        //               ^ fast ends at a nullptr
        //       ^slow ends here
        // 
        // So in both cases, we can terminate the while loop and guarantee that the slow pointer's next is the start of the 2nd half of the list
        // if the condition is fast->next != nullptr (for even) and fast != nullptr (odd)
        while(fast && fast->next)
        {
            // Advance slow by 1
            slow = slow->next;

            // Advance fast by two, this is guaranteed to work, try it with slow and fast pointer with a 
            // odd and even numbered list. We will never go out of bounds.
            // Think of it like this, if fast is currently on a not null node, or on null, then the loop condition triggers and we won't run anymore.
            // this means, fast must be at the penultimate node or earlier. If it's on the penultimate, then
            // fast->next is the last node and fast->next->next is nullptr, both are valid.
            fast = fast->next->next;
        }


        // 2) Reverse right half

        // Now we reverse the 2nd half of the list, which starts at slow->next
        auto rhsCurrent = slow->next;

        // Terminate the LHS
        slow->next = nullptr;
        
        auto prev = PtrListNode{nullptr};
        while(rhsCurrent)
        {
            auto next = rhsCurrent->next;
            rhsCurrent->next = prev;
            prev = rhsCurrent;
            rhsCurrent = next;
        }

        // Now combine these two!
        auto lhsHead = head;
        auto rhsHead = prev;
        
        // This is pretty damn smart. I works if you try on an odd and then an even list:
        // Even:
        // 1->2->null
        // 4->3
        //   On the last iteration, point 2 to 3, then 3 to what 2 WAS pointing to (null)
        //
        // Odd:
        // 1->2->3
        // 4->5
        //   On the last iteration, point 2 to 5, then 5 to what 2 WAS pointing to (3). 3 is already pointing to null, so we are done!
        while(rhsHead)
        {
            auto next1 = lhsHead->next;
            auto next2 = rhsHead->next;
            
            lhsHead->next = rhsHead;
            rhsHead->next = next1;

            lhsHead = next1;
            rhsHead = next2;
        }
    }
};

// This is my first attempt at the solution. After watching NeetCode's video, I realised that my approach was
// not element, so I am trying again, see the solution above.
class SolutionOptimisedSpaceFirstAttempt {
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

        // Terminate the RHS
        slow->next = nullptr;
        
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
        
        auto tmp = ListNode{};
        prev = &tmp;
        while(lhsHead)
        {
            auto next1 = lhsHead->next;
            prev->next = lhsHead;

            if(rhsHead == nullptr)
            {
                prev = lhsHead;
                break;
            }
            auto next2 = rhsHead->next; // this is where the nullptr access happened.
            prev->next->next = rhsHead;

            prev = rhsHead;
            lhsHead = next1;
            rhsHead = next2;
        }

        prev->next = nullptr;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto l5 = ListNode{5};
    auto l4 = ListNode{4, &l5};
    auto l3 = ListNode{3, &l4};
    auto l2 = ListNode{2, &l3};
    auto l1 = ListNode{1, &l2};
    SolutionOptimisedSpace{}.reorderList(&l1);

    auto ii = 42;

    return 0;
}

