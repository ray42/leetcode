/*
https://leetcode.com/problems/majority-element/solutions/4713694/beats-100-users-c-java-python-javascript-2-approaches-explained/

Approach 2 is interesting!
We know that the majority element has frequency greater than floor(n/2).
This means that it is greater than all the other frequencies combined.
Given this fact, we can pick a number and start counting it's frequency
    but we also decrement the frequency if we come across an element that is not the number we picked.

    We can think of it as pitting the majority element against all other elements, marking them off one by one.
    Eventually, the majority element will win because it has more frequency than all other numbers combined.
*/
#include <vector>
#include <unordered_map>

class Solution 
{
public:
    auto majorityElement(const std::vector<int>& nums) -> int
    {
        const auto majorityFrequency = nums.size()/2;
        auto numsFrequency = std::unordered_map<int, int>{};
        for(const auto& n : nums)
        {
            if(++numsFrequency[n] > majorityFrequency)
            {
                return n;
            }
        }
        return 0;
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution{}.majorityElement({3,2,3}); 
    return 0;
}
