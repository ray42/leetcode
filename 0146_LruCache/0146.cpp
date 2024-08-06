#include <unordered_map>
#include <memory>


struct Node
{
    int key;
    int val;

    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;
    
    Node(int _key, int _val) : Node(_key, _val,nullptr, nullptr)
    {

    }

    Node(int _key, int _val, Node* _prev, Node* _next) : key(_key), val{_val}, prev{_prev}, next{_next}
    {

    }
};


class LRUCache {
public:

    LRUCache(int _capacity): m_capacity{_capacity}
    {
        
    }
    
    int get(int key) {
        // Return the value but also put the node at the front of the list
        if(auto it = m_map.find(key); it != m_map.end())
        {
            auto [key, node] = *it;

            move_to_head(node);
            
            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value)
    {
        if(auto it = m_map.find(key); it != m_map.end())
        {
            it->second->val = value;

            move_to_head(it->second);
        }
        else
        {
            // Insert at front and insert into map
            auto node = std::make_shared<Node>(key, value);
            set_head(node);
            m_map.insert({key,node});

            while(m_map.size() > m_capacity)
            {
                m_map.erase(m_tail->key);
                removeFromList(m_tail);
            }
        }
    }

private:

    void move_to_head(std::shared_ptr<Node> node)
    {
        if(node != m_head)
        {
            removeFromList(node);
            set_head(node);
        }
    }

    void removeFromList(std::shared_ptr<Node> node)
    {
        if(m_tail == nullptr || m_tail == m_head)
        {
            // If m_tail == nullptr, there is nothing to remove.
            // if m_tail == m_head, there is one node to remove.
            // In both cases, we set the head and tail to null
            m_head = nullptr;
            m_tail = nullptr;
            
            node->next = nullptr;
            node->next = nullptr;
            return;
        }
        else if(node == m_head) 
        {
            auto nextNode = m_head->next;

            // This is OK, we know that there is at least 2 nodes
            nextNode->prev = nullptr;


            node->next = nullptr;
            node->prev = nullptr;

            m_head = nextNode;
        }
        else if(node == m_tail)
        {
            auto prevNode = m_tail->prev;

            // This is OK, we know that there is at least 2 nodes
            prevNode->next = nullptr;
            
            node->next = nullptr;
            node->prev = nullptr;

            m_tail = prevNode;
        }
        else
        {
            auto prevNode = node->prev;
            auto nextNode = node->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            node->next = nullptr;
            node->prev = nullptr;
        }
    }

    void set_head(std::shared_ptr<Node> node)
    {
        if(node == m_head)
        {
            return;
        }
        node->next = m_head;
        node->prev = nullptr;
        
        // If this is the first node to be head, then m_head if null
        if(m_head != nullptr)
        {
            m_head->prev = node;
        }
        m_head = node;

        // If m_tail is null, it means that this is the first node, so we set the tail too.
        if(!m_tail)
        {
            m_tail = node;
        }
    }

    int m_capacity{0};
    int m_nNodes{0};
    std::shared_ptr<Node> m_head{nullptr};
    std::shared_ptr<Node> m_tail{nullptr};

    std::unordered_map<int, std::shared_ptr<Node>> m_map{};
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

auto main(int argc, char* argv[]) -> int
{
    return 0;
}


