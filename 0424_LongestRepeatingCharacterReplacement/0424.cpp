/*
You are given a string s and an integer k. 
You can choose any character of the string and change it to any other uppercase English character. 
You can perform this operation at most k times.

Return the length of the longest substring containing the same letter 
you can get after performing the above operations.

Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.

------------------------
Solution notes:

So, we use a sliding window approach.
ABAB
L
R

First we identify the conditions to move the L and R pointer.
Think of it this way, the questions to ask yourself is:
1) *what is a valid string*, 
2) and as we move R to the right, *when does it become invalid*?
3) The last part is to move L until the string becomes valid again.

The string is valid if, after changing at most k characters, all characters of the string are the same.
Say we have:
BBCABB, k = 2 
this is a valid string because there are two characters that we can replace with B to make BBBBBB.
Is this valid?
BBCAABB
No, because we cannot replace CAA with B's, since we can only do this k=2 times.
So, we need something like:
LengthOfString - NumberOfBs <= 2

So, we see that we want:
LengthOfString - MaxFrequencyCharacter <= k

that will give us a valid string!

Once we have moved R so that that substring becomes invalid, we move L until be comes valid again.

How do we calculate MaxFrequencyCharacter? We will maintain a hash map of characters to the frequencies of the substring under consideration
I.e. the substring 
BBCAABB
L     R

and so we do:
LengthOfString - MaxFrequencyCharacter <= k

where MaxFrequencyCharacter is the max number is that hash map.

------------------------
Note: Why, when we move the L pointer, we move it until it's valid again? What is the justification for this?
Well, we know that e.g.
say this is now invalid.
0123456
xxxxxxx
L   R
So we move L:
0123456
xxxxxxx
 L  R
If it is still invalid, why do we keep moving L instead of moving R backwards?
Because we know that the max length we have is now 4, if we move L, the max length
is at most 3. If we move R backwards the max length must be less than 3.
And if we eventually move R forward again, we know that we cannot get more than 3 before 
it becomes invalid again.
----------------------
Notes on MaxFrequencyCharacter:
In the above algorithm, we look up the MaxFrequencyCharacter from the hash map at every iteration. 
Look at the condition again:

LengthOfString - MaxFrequencyCharacter <= k

We want to increase LengthOfString whilst having the number of characters to be replaced be less than k
It is evident that we need MaxFrequencyCharacter to increase too. So what does this tell us?

THIS TELLS US THAT:
LengthOfString = MaxFrequencyCharacter + NumberOfCharactersToBeReplaced(k)

since k is constant, we know that LengthOfString wil increase iff MaxFrequencyCharacter increases!
That is, we can only improve on LengthOfString if MaxFrequencyCharacter increases, we don't care about decreases.
Thus, we can only keep track of the largest MaxFrequencyCharacter found.

Watch Leetcode's video on this, it's real good. I also need to explain this better.

IN FACT, let's try to explain this.

length - maxf <= k
6 - 4 <= k

So our result is 6. The only way we can improve upon 6 is if maxf increases too.
So if maxf happens to be less than 4, we can still use 4, the we just won't update the result to 
anything bigger than 6 and 
length - maxf <= k still holds true.

*/
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    auto characterReplacement(const std::string& s, int k) -> int
    {
        // So, I know that I have to start both L and R at the same place and normally, I'd do something like:
        // auto L = 0, R = 0,
        // and use a while loop. However, we know that the R pointer needs to keep moving forward one at a time
        // then if the substring becomes invalid, only then that we move L. 
        // **So we can actually use a for loop**
        // But how do we ensure that L never goes beyond R? Because we know that a string of 1 character is valid.
        // and so, if L == R, then this becomes valid and R has to move.
        auto frequencies = std::unordered_map<char,int>{};

        auto result = 0;
        auto L = 0;
        const auto sSize = s.size();
        for(auto R = 0; R < sSize; ++R)
        {
            ++frequencies[s[R]];
            // Is this valid?
            auto substringLength = R - L + 1;
            auto maxFrequency = std::max_element(
                std::begin(frequencies), 
                std::end(frequencies), 
                [](const auto& p1, const auto& p2)
                {
                    return p1.second < p2.second;
                })->second;

            while(substringLength - maxFrequency > k)
            {
                // Keep shifting L until the string is valid
                --frequencies[s[L]];
                ++L;
                substringLength = R - L + 1;
                auto maxFrequency = std::max_element(
                std::begin(frequencies), 
                std::end(frequencies), 
                [](const auto& p1, const auto& p2)
                {
                    return p1.second < p2.second;
                })->second;
            }

            result = std::max(R - L + 1, result);
        }
        return result;
    }
};

// Same as above but with maxFrequency optimisation
// Recall that we only need to calculate the max frequency if it changes
class SolutionOptimised {
public:
    auto characterReplacement(const std::string& s, int k) -> int
    {
        // So, I know that I have to start both L and R at the same place and normally, I'd do something like:
        // auto L = 0, R = 0,
        // and use a while loop. However, we know that the R pointer needs to keep moving forward one at a time
        // then if the substring becomes invalid, only then that we move L. 
        // **So we can actually use a for loop**
        // But how do we ensure that L never goes beyond R? Because we know that a string of 1 character is valid.
        // and so, if L == R, then this becomes valid and R has to move.
        auto frequencies = std::unordered_map<char,int>{};

        auto result = 0;
        auto L = 0;
        const auto sSize = s.size();
        auto maxFrequency = 0;
        for(auto R = 0; R < sSize; ++R)
        {
            ++frequencies[s[R]];
            // Is this valid?
            auto substringLength = R - L + 1;
            maxFrequency = std::max(maxFrequency, frequencies[s[R]]);

            while(substringLength - maxFrequency > k)
            {
                // Keep shifting L until the string is valid
                --frequencies[s[L]];
                ++L;
                substringLength = R - L + 1;
            }

            result = std::max(R - L + 1, result);
        }
        return result;
    }
};

auto main(int argc, char* argv[]) -> int
{
    //auto sss = Solution{}.characterReplacement("ABAB", 2);
    auto sss = Solution{}.characterReplacement("AABABBA", 1);
    return 0;
}

