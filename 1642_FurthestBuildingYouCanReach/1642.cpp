/*
https://leetcode.com/problems/furthest-building-you-can-reach/description/
*/
#include <vector>

class Solution {
public:
    auto furthestBuilding(const std::vector<int>& heights, int bricks, int ladders) -> int
    {
        // Use the ladder for the largest height
        // Then see if we can reach the ladder and see how far we can go-> we have our answer
        // If we cannot reach the ladder, then from the first building to the ladder and determine the next largest height.
        //
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}

