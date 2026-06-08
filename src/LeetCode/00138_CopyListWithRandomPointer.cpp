
/*
The difficulty here is how to identify the random node to assign to the random pointer.
Think about it, even if we made a deep point of the singly linked list part:

7->13->11->10->1->null (this is a deep copy)

How on Earth do we identify which nodes in there given the original linked list?
(original here:)

7->13->11->10->1->null
^--|   |^---|     ^
^------|^---|     ^
|-----------------^

E.g. We know that 10's random pointer is 11, but how do we find out where 11 is in the deep copy?
We can't even rely on the value and do a search since the value is not unique.

--------------------------------------------------------
Solution:
We describe two solutions, with additional storage and without additional storage, to identify the random nodes
--------------------------------------------------------

With additional storage:
----------------------------
We use a map where the key is the original node and the value is the new node.
Then, we can identify both the next and random node in the old list by looking it up in the map.
In other words, let the old list be

a->b->c->null (old)

The new (copied) nodes will be denoted by an apostrophe.

Then:
Loop through the original node list:
  a' = mapOriginalToCopy[a]
  a'->next = mapOriginalToCopy[a->next]
  a'->random = mapOriginalToCopy[a->random]

Without additional storage:
----------------------------

Original: a->b->c->null (old)

Step 1: Create the deep copy

a'->b'->c'->null

Step 2: Get the random pointer by first interweaving:
a->a'->b->b'->c->c'->null

Given a, then random pointer to a' would be to follow the random pointer of a, then get the next, e.g.

a->a'->b->b'->c->c'->null
|------^

The random pointer of a is b. So we follow a to b, then we know that the random pointer of a' will be the next of b (i.e. b')

Step 3:
untwine the two:
Can use a do while loop and keep untwining until the next pointer of the copied node is null.
*/

#include <unordered_map>

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class SolutionAdditionalStorage {
public:
    using PtrNode = Node*;
    Node* copyRandomList(Node* head)
    {
        auto originalToCopy = std::unordered_map<PtrNode, PtrNode>{{nullptr,nullptr}};
        auto currentOrig = head;
        while(currentOrig)
        {
            originalToCopy[currentOrig] = new Node{currentOrig->val};
            currentOrig = currentOrig->next;
        }

        currentOrig = head;
        while(currentOrig)
        {
            auto copy = originalToCopy[currentOrig];
            copy->next = originalToCopy[currentOrig->next];
            copy->random = originalToCopy[currentOrig->random];
            currentOrig = currentOrig->next;
        }
        return originalToCopy[head];
    }
};


/*
Without additional storage:
----------------------------

Original: a->b->c->null (old)

Step 1: Create the deep copy

a'->b'->c'->null

Step 2: Get the random pointer by first interweaving:
a->a'->b->b'->c->c'->null

Given a, then random pointer to a' would be to follow the random pointer of a, then get the next, e.g.

a->a'->b->b'->c->c'->null
|------^

The random pointer of a is b. So we follow a to b, then we know that the random pointer of a' will be the next of b (i.e. b')

Step 3:
untwine the two:
Can use a do while loop and keep untwining until the next pointer of the copied node is null.
*/
class SolutionNoAdditionalStorage {
public:
    Node* copyRandomList(Node* head) 
    {
        if(!head) return nullptr; // The below doesn't handle empty lists well since I do head->val.

        // Step 1 - make a deep copy of the list
        auto currentOrig = head;

        // Keep track of the new head because we need to traverse the new list a couple of times
        auto headNew = new Node{head->val};
        auto currentNew = headNew;
        while(currentOrig)
        {
            currentNew->next = currentOrig->next != nullptr ? new Node{currentOrig->next->val} : nullptr;
            
            currentNew = currentNew->next;
            currentOrig = currentOrig->next;
        }

        // Step 2 - merge the two lists - maybe we can combine this step with step 1, but I want to try doing it separately first
        currentOrig = head;
        currentNew = headNew;
        while(currentNew)
        {
            // Keep track of the next since we will break links to them
            auto nextOrig = currentOrig->next;
            auto nextNew = currentNew->next;

            // Point the currentOrig to currentNew and currentNew to currentOrig->next, in other words:
            // if the two lists are
            // a - b...
            // a'- b'...
            // 
            // then we do this:
            // a  b
            // | /
            // a'
            currentOrig->next = currentNew;
            currentNew->next = nextOrig;

            currentOrig = nextOrig;
            currentNew = nextNew;
        }

        // Step 3 - Join the random pointers
        auto currentMerged = head;
        while(currentMerged)
        {
            currentMerged->next->random = currentMerged->random == nullptr ? nullptr : currentMerged->random->next;
            currentMerged = currentMerged->next->next;
        }

        // Step 4 - split the list
        currentMerged = head;
        currentOrig = head;
        currentNew = headNew;
        while(currentMerged)
        {
            // Get the two "next" nodes
            // a->a'->b->b'->null
            auto nextOrig = currentMerged->next->next;
            auto nextNew = currentMerged->next->next == nullptr ? nullptr : currentMerged->next->next->next;

            currentNew->next = nextNew;
            currentOrig->next = nextOrig;

            currentNew = currentNew->next;
            currentOrig = currentOrig->next;

            currentMerged = currentOrig;
        }

        // Step 5 - return the list of the new list
        return headNew;
    }
};


auto main(int argc, char* argv[])->int
{
    auto n0 = Node{7};
    auto n1 = Node{13};
    auto n2 = Node{11};
    auto n3 = Node{10};
    auto n4 = Node{1};

    n0.next = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = nullptr;

    n0.random = nullptr;
    n1.random = &n0;
    n2.random = &n4;
    n3.random = &n2;
    n4.random = &n0;

    auto iii = SolutionNoAdditionalStorage{}.copyRandomList(&n0);
    auto fdfs = 42;

    return 0;
}
