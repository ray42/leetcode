/*
Easy: https://leetcode.com/problems/assign-cookies/

RAYNOTES:

First, we sort the arrays in ascending order
g = [1,2], 
s = [1,2,3]

Now we can use two pointers, say i and j, indexing into g and s, respectively.
For gi, we check if gi <= sj, if it is, then we can assign it and increment both gi and sj.
    The point is that, because we have sorted it, we know that once we move gi to g{i+1}, then it could not possibly be
    satisfied by any entries sj to the left.
So we can keep doing this.

Answer is here, pretty good: https://leetcode.com/problems/assign-cookies/
*/
#include <vector>
#include <ranges>
#include <algorithm>
#include <cstdlib>

class Solution {
public:
    auto findContentChildren(std::vector<int>& g, std::vector<int>& s)  -> int
    {
        std::ranges::sort(g);
        std::ranges::sort(s);

        auto count = 0;
        auto i = 0; // index into g
        auto j = 0; // index into s

        while(i < g.size() && j < s.size())
        {
            // If the size of the cookie is greater than or equal to the child's greed,
            // assign the cookie to the child and move both pointers
            if(g[i] <= s[j])
            {
                ++count;
                ++i;
                ++j;
            }
            else
            {
                // Move the cookie pointer to the next cookie, regardless of assignment
                ++j;
            }
        }
        return count;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return EXIT_SUCCESS;
}

