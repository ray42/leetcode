
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
We describe two solutions, with additional storage and without additional storage.
--------------------------------------------------------

With additional storage:





*/


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
    Node* copyRandomList(Node* head) {
        
    }
};


class SolutionNoAdditionalStorage {
public:
    Node* copyRandomList(Node* head) {
        
    }
};
