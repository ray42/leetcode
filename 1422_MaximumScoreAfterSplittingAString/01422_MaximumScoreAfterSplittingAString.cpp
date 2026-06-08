/*
Easy: https://leetcode.com/problems/maximum-score-after-splitting-a-string

Ray Notes:

1) Naive Method:
We can loop from left to right, splitting the string and calculating the left and right sub-string values, summing them to see if we need to update  the max or not.
Complexity:
For each n-1 splits, we need to loop through the values again to calculate the sum, this makes it n^2.

2) Improved
We calculate how many ones are in s, this is the right value. The left value is initialised to 0.
Then we loop through the chars in s from s[0] to s[n-2] (n-2 because this is how the string splits, we need one on the right)
  E.g. ifs = 1234, then the splits are:
  1  234 // represented by s[0]
  12 34  // represented by s[1]
  123 4  // represented by s[2] = n-2 = 4-2 = 2.

Each iteration of the loop represents a "split". So s[0] is the split s[0], s[1..n-1]
  We update the left and right:
    if the current char is 0, left = left+1
    if the current char is 1, right = right-1
  sum the updated left and right to see if we need to update the max sum.

Complexity: n
*/

#include <string>
#include <algorithm>

class Solution 
{
public:
    auto maxScore(const std::string& s) -> int
    {
        auto leftValue = 0;
        auto rightValue = std::ranges::count(s,'1');
        auto maxValue = -1;
        const auto secondLast = s.size()-1;
        for(auto i = 0; i < secondLast; ++i)
        {
            // I noticed that as we loop right the chars, we either increase or decrease the current sum.
            // This means we can get away with using only variable, see the solution below!
            if(s[i] == '0')
            {
                ++leftValue;
            }
            else
            {
                --rightValue;
            }
            if(const auto sumLeftRightValues = leftValue + rightValue; sumLeftRightValues > maxValue)
            {
                maxValue = sumLeftRightValues;
            }
        }
        return maxValue;
    }
};

class Solution2 
{
public:
    auto maxScore(const std::string& s) -> int
    {
        auto rightValue = std::ranges::count(s,'1');
        auto maxValue = -1;
        for(auto i = 0; i < s.size()-1; ++i)
        {
            // I noticed that as we loop right the chars, we either increase or decrease the current sum.
            // This means we can get away with using only variable, see the solution below!
            if(s[i] == '0')
            {
                ++rightValue;
            }
            else
            {
                --rightValue;
            }

            if(rightValue > maxValue)
            {
                maxValue = rightValue;
            }
        }
        return maxValue;
    }
};

auto main(int argc, char * argv[])->int
{
    return 0;
}
