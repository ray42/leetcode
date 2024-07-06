/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. 
The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. 
Each hour, she chooses some pile of bananas and eats k bananas from that pile. 
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

--------------------------------
In other words, we need to find the lowest k such that we can eat all the bananas in h hours.
As k gets lower, the hours get higher,
As k gets higher, the hours get lower.

Input: piles = [3,6,7,11], h = 8
Output: 4

Take the ceiling, k = 4:
3/4+6/4+7/4+11/4 = 1+2+2+3 = 8

if k = 3:
3/3+6/3+7/3+11/3 = 1+2+3+4 = 10 > 8, so we need to eat faster

if k = 5:
3/5+6/5+7/5+11/5 = 1+1+1+3 = 6 < 8, so we *can* eat slower.

--------------------------------

Algorithm: 

let k = 1, ..., max(piles), be the search space.
let k = middle.

We use binary search for the smallest k such that sum ceiling(p_i/k) <= h

if sum ceiling(p_i/k) > h, 
    we need to eat faster, so we look right for larger k
else if sum ceiling(p_i/k) < h, 
    there is room to eat slower, so we look left for smaller k
otherwise, it is equal so we return immediately.
*/

#include <vector>
#include <cmath>
#include <limits>
#include <numeric> // apparently for accumulate, why is this not in algorithm???
#include <algorithm>

using ll = long long;
class Solution {
public:
    int minEatingSpeed(const std::vector<int>& piles, int h)
    {
        auto L = ll{1};
        auto R = ll{*std::max_element(piles.begin(), piles.end())};
        auto k = std::numeric_limits<ll>::max();
        
        while(L <= R)
        {
            auto M = (L+R)/2;
            if(M == 6)
            {
                auto iii = 42;
            }

            // This is very interesting. I need to force accumulate to return a ll, but the elements in pile is of type int.
            // So we have to explicitly call the accumulate function with type information. This is for the test case:
            // piles = [805306368, 805306368, 805306368]
            // h = 1000000000
            auto hours = std::accumulate<decltype(piles.begin()), ll>(piles.begin(), piles.end(), 0, [&](ll currentSum, ll pi)
            {
                return currentSum + static_cast<ll>(std::ceil(pi/static_cast<double>(M)));
            });
            
            if(hours > h)
            {
                // Eat faster, look right
                L = M+1;
            }
            else if(hours <= h)
            // NOTE: This is important, we cannot have a separate == and return immediately, if hours == h.
            // This is because, even if we have found a k such that hours == h, an even smaller k might exist.
            // E.g. piles = [1,1,1,999999999], h=10. We will reach 156250000 first, which gives hours = 10
            // but this is due to the rounding in ceil. An even smaller one exists: k = 142857143, so we have to keep
            // searching until L<=R becomes false.
            {
                k = std::min(k,M);
                // We might be able to eat slower, look left
                R = M-1;
            }
        }
        
        // This k is as best as we can get.
        return k;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.minEatingSpeed({805306368,805306368,805306368},1000000000);
    auto iiii = 42;
    return 0;
}

