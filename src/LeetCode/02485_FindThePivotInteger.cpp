/*
n = 8 -> 1,2,3,4,5,6,7,8
the pivot is 6 since 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21
I feel that we can define the two parts mathematically and thus work this out mathematically.
sum of natural numbers is n(n+1)/2. Let's represent the pivot number by p. Then we have:
sum_1^p = p(p+1)/2 // left hand side
sum_p^n = sum_1^n - sum_1^{p-1} = n(n+1)/2 - (p-1)p/2
Equate both sides: 
p(p+1)/2 = n(n+1)/2 - (p-1)p/2
p^2/2+p/2 = n(n+1)/2 - p^2/2 + p/2
p^2 = n(n+1)/2
p = +/- sqrt(n(n+1)/2)
Since we are after positive integers, we have
p = sqrt(n(n+1)/2) if is positive
    else is -1.

Let's test: sqrt(8*9/2) = sqrt(36) = 6 - this is an answer.
Basically, a good way to think about this is, is n(n+1)/2 is a square number, where n = 1 .. 1000
Let's use this :)
*/

#include <cmath>
#include <iostream>

// Interesting solution from https://leetcode.com/problems/find-the-pivot-integer/solutions/4866463/beat-100-full-explanation-with-pictures/
// if x%1 != 0 check if the value of x is not an integer.
//class Solution {
//public:
//    auto pivotInteger(const int n) -> int
//    {
//        const auto sr = sqrt(n*(n+1)/2);
//        
//
//        return fmod(sr, 1.0) != 0 ? -1 : static_cast<int>(sr);
//    }
//};

class Solution {
public:
    auto pivotInteger(const int n) -> int
    {
        const auto sumOfN = n*(n+1)/2;
        
        const auto sr = static_cast<int>(std::sqrt(sumOfN));

        return sr*sr == sumOfN ? sr : -1;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto a = 3.14;
    auto b = fmod(a, 1.0);
    std::cout << "a%1 is: " <<  b << '\n';
    return 0;
}

