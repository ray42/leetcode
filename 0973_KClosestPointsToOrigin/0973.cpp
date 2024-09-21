/*
Basically, we need to keep track of the k smallest elements. What are the elements in this case?

It's the distance to the origin. This is sqrt(x^2 + y^2), however, we don't need to calculate that.
We can simply calculate x+y.

We use a max heap since we want to keep track of the kth smallest only.
*/

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
#include <cmath>

// NOTE: This is a dumb way to do it. If we make a vector of vectors, then put the distance first, we can just use a priority queue
// Look at NC's video if I'm not sure what I mean. Write an updated comment after I have implemented NC's solution.
class Solution {
public:

    struct PointWithDistance
    {
        PointWithDistance(const std::vector<int>& p) : point{p}, distance{std::sqrt(std::pow(p[0],2) + std::pow(p[1],2))}
        {
        }

        std::vector<int> point;
        double distance;
    };
    std::vector<std::vector<int>> kClosest(const std::vector<std::vector<int>>& points, int k)
    {
        // There is at least one point
       
        // Max Heap
        auto compare = [](const PointWithDistance& lhs, const PointWithDistance& rhs){
            return lhs.distance < rhs.distance;
        };
        auto pq = std::priority_queue<PointWithDistance, std::vector<PointWithDistance>, decltype(compare)>{};
        pq.push(PointWithDistance{points[0]}); // There is at least one element 
        for(auto i = 1; i < points.size(); ++i)
        {
            if(pq.size() < k ||  std::sqrt(std::pow(points[i][0],2) + std::pow(points[i][1],2)) < std::sqrt(std::pow(pq.top().point[0],2) + std::pow(pq.top().point[1],2)))
            {
                pq.push(PointWithDistance{points[i]});
                if(pq.size() > k)
                {
                    pq.pop();
                }
            }
        }

        auto ret = std::vector<std::vector<int>>{};
        while(pq.size() > 0)
        {
            ret.push_back(pq.top().point);
            pq.pop();
        }
        return ret;
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto ii = Solution{}.kClosest({{1,3},{-2,2}}, 1);
    auto iii = 42;
    return 0;
}

