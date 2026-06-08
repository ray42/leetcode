
#include <vector>
#include <queue>

class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones)
    {
        auto pq = std::priority_queue<int, std::vector<int>, std::less<int>>{stones.begin(), stones.end()};

        while(pq.size() > 1)
        {
            auto y = pq.top();
            pq.pop();
            auto x = pq.top();
            pq.pop();

            if(y>x) pq.push(y-x);
        }

        return pq.empty() ? 0 : pq.top();
    }
};
