/*
EASY: https://leetcode.com/problems/count-of-matches-in-tournament

My Notes:
 We can do it iteratively or recursively and it'll be quite easy. But I am
 trying to come up with intuition of how I can do it mathematically.

 I can start with:
 n  #matches
 1  0
 2  2/2 = 1
 3  (3-1)/2 + f((3-1)/2 + 1) = 1 + 1 = 2
 4  4/2     + f(4/2)         = 2 + 1 = 3
 5  (5-1)/2 + f((5-1)/2 + 1) = 2 + 2 = 4
 6  6/2     + f(6/2)         = 3 + 2 = 5
 7  (7-1)/2 + f((7-1)/2 + 1) = 3 + 3 = 6
 8  8/2     + f(8/2)         = 4 + 3 = 7
 9  (9-1)/2 + f((9-1)/2 + 1) = 4 + 4 = 8

We can see that 
1) if n is even, then we have
n/2 + (n/2 + 1) = n-1
2) if n is odd, then we have
(n-1)/2 + (n-1)/2 = n-1

OMG! That is the formula!

This is from the leetcode discussions:
There are n teams participating in the tournament.
After each match 1 team is eliminated.
n-1 teams needs to be eliminated: hence n-1 matches.
*/

class Solution {
public:
    auto numberOfMatches(const int& n) -> int
    {
        return n-1;
    }
};

auto main(int argc, char* argv[]) -> int
{
    return 0;
}
