/*
Looking at https://leetcode.com/problems/median-of-two-sorted-arrays/editorial/,

I really don't fully understand approach 2.
However, I do understand approach 1 & 3, which I will detail here.

Approach 1 (linear): Two pointer based:

We need to get to the middle of the sorted array. Let
A =   [1,2,3,4,5,6,7,8] n=8
B =   [1,2,3,5] n=4
A+B = [1,1,2,2,3,3,4,5,5,6,7,8] n=12, median = avg(E_n/2, E_{n/2 +1})th element.

---
Aside (this is important later when we deal with the loop conditions): 
The way we calculate the middle element for 0 based vs 1 based is different:

Note: We are doing integer division here
Odd elements:
0 based:  0,1,2,3,4  M = 4/2 = 2
1 based: [1,2,3,4,5] M = 5/2 + 1 = (5+1)/2 = 3

Even elements:
0 based:  0,1,2,3  M = avg(3/2, 3/2 + 1)
1 based: [1,2,3,4] M = avg(4/2, 4/2 + 1)
---
Algorithm

    1) Get the total size of two arrays m + n
        If m + n is odd, we are looking for the (m + n)/2-th element (RRR42 I assume this is 0 based, look at the aside).
        If m + n is even, we are looking for the average of the (m + n) / 2-th and the (m + n) / 2 + 1-th elements.

    2) Set two pointers p1 and p2 at the beginning of arrays nums1 and nums2.

    3) If both p1 and p2 are in bounds of the arrays, compare the values at p1 and p2:
        If nums1[p1] is smaller than nums2[p2], we move p1 one place to the right.
        Otherwise, we move p2 one place to the right.

       If p1 is outside nums1, just move p2 one place to the right.
       If p2 is outside nums2, just move p1 one place to the right.

    4) Get the target elements and calculate the median:
        If m + n is odd, repeat step 3 by (m + n + 1) / 2 times and return the element from the last step. (RRR42 this is the 1 based version)
        If m + n is even, repeat step 3 by (m + n) / 2 + 1 times and return the average of the elements from the last two steps. (RRR42 this is the 1 based version)

----------------------------

Approach 3 (remember, I am not doing approach 2)

Intuition

Let
A = [1,2,3,4,5,6,7,8], N = 8
B = [1,2,3,5], M = 4
What is the median?
       0 1 2 3 4 5 6 7 8 9 10 11
A+B = [1,1,2,2,3,3,4,5,5,6,7, 8], N+M=12, 
Because it is even, we need avg(6,6+1)'s element:
=(3+4)/2 = 3.5 (1 based)

The * denotes median element(s)

       1 2 3 4 5 6  7  8 9 10 11 12
A+B = [1,1,2,2,3,3*,4*,5,5,6, 7, 8]

What about odd?
       1 2 3 4 5 6 7  8 9 10 11 12 13
A+B = [1,1,2,2,3,3,4*,5,5,6, 7, 8, 9] 

When we need only the 7th element, that is 13/2 + 1 (integer division).
--- The partitioning:
If we divide the number of elements by 2, we get the position of the median elements:
Even:
12/2 = 6
       1 2 3 4 5 6    7 8 9 10 11 12
A+B = [1,1,2,2,3,3*],[4*,5,5,6, 7, 8]
       A+B_Left       A+B_Right
Odd:
13/2 = 6
       1 2 3 4 5 6   7 8 9 10 11 12 13
A+B = [1,1,2,2,3,3],[4*,5,5,6, 7, 8, 9] (So we need to do the left partition + 1).

Now I want to work backwards. Let's split the [A+B] back into the two arrays original arrays but we keep
the partitions we created for [A+B] and see where the two partitions lie, that way we hope to come up with
a method which helps us re-create the partitioning without us having to join the two arrays together:

Without Loss of Generality, we choose the even [A+B]:

A = [1,2,3] ,[4*,5,6,7,8], N = 8
     A_L      A_R
B = [1,2,3*],[5], M = 4
     B_L      B_R

We see that all the elements from A_L and B_L are less than or equal to all the elements
from A_R and B_R. This is because they can from A+B_Left and A+B_Right.
In particular, if we look at the boundary:

A = [1,2,3] ,    [4*,5,6,7,8], N = 8
         max_A_L  min_A_R

B = [1,2,3*],    [5], M = 4
         max_B_L  min_B_R

(Good condition): it must be that max_A_L and max_B_L are equal to or less both right boundaries min_A_R and min_B_R:
max_A_L <= min_A_R and min_B_R
max_B_L <= min_A_R and min_B_R

If max_A_L > min_A_R and min_B_R it means we need less of A (we only need to check if max_A_L > min_B_R since max_A_L < min_A_R is a given)
  -> we continue to search for the partition on the right half of B (we only need to check if max_B_L > min_A_R since max_B_L < min_B_R is a given)

If max_B_L > min_A_R and min_B_R it means we need less of B 
  -> we continue to search for the partition on the left half of B

So that's it! That can be our condition!

------- Example (Extreme, only elements from A)

A = [1,2,3,4,5,6,7] N_A = 7
B = [7,8,9] N_B = 3

N_A+B = 10, is even, so we know we need to average the 5th (10/2) and 6th element of the merged array.
We always want to do binary search on the smaller one, so how much of B do we take? Let's just go half way:

--- Iteration 1

B = [7,8,9], so the partitions are:
     R M R
     
A = [1,2,3],[4,5,6,7]
B = [7,8],[9]

We take 3 elements as the LHS of A because we know the total number of elements on the LHS must be
5, and 5-2=3.

Now check our condition:
A = [1,2,3],     [4,5,6,7]
         max_A_L  min_A_R
B = [7,8],       [9]
        max_B_L  min_B_R

max_A_L <= min_B_R -> 3 <= 9 is true
max_B_L <= min_A_R -> 8 <= 4 is false, so we look left of max_B_L

--- Iteration 2

B = [7]
     R
     M
     L

Now check our condition:
A = [1,2,3,4],     [5,6,7]  5-1 = take 4 elements as A_left
           max_A_L  min_A_R
B = [7],     [8, 9]
     max_B_L  min_B_R

Condition check:
max_A_L <= min_B_R -> 4<=8 is true
max_B_L <= min_A_R -> 7<=5 is false, need less of B, so look left

--- Iteration 3

[]
R < L This means we take nothing from B and only elements from A:

A = [1,2,3,4,5],     [6,7]    5-0 = take 5 elements as A_left
             max_A_L  min_A_R
B =         []       [7,8, 9]
             max_B_L  min_B_R

Condition check:
max_A_L <= min_B_R -> 5<=8 is true
max_B_L <= min_A_R -> -inf<=6 is true. Note we use -inf when there are no elements on the left.
                                       We will use +inf for when there are no elements on the right.

IMPORTANT: 
Recall that we need 5th (10/2) and 6th element of the merged array (since num elements is even)
The 5th element is in the left half of the merged array and 6th element is the right half of the merged array

How do we get this? Easy:
5th element: max(max_A_L,max_B_L) = max(5,-inf) = 5
6th element: min(min_A_R,min_B_R) = min(6,7) = 6

(5+6)/2=5.5

-----

Note: If the total number of elements is odd, we simply return the 

(N/2 +1)th element. E.g.

[1,2,3,4,5], 5/2 = 2, 2+1 = 3, return the 3th element, which is min(min_A_R,min_B_R),
i.e. the smaller of the two right halves.

Let's code this up!!!

*/


#include <vector>
#include <cassert>
#include <limits>

//#define CATCH_CONFIG_MAIN
//#include "./../common/catch_amalgamated.hpp"


class SolutionLinear {
public:

    // Pointers into the two arrays nums1 and nums2
    int p1 = 0;
    int p2 = 0;

    // Returns the next number in the sequence as if nums1 and nums2 were merged.
    // E.g. if getNextFromMerged is called for the first time, it would return the first number in the merged sequence.
    auto getNextFromMerged(const std::vector<int>& nums1, const std::vector<int>& nums2) -> int
    {
        const auto nums1Size = std::ssize(nums1);
        const auto nums2Size = std::ssize(nums2);
        if(p1 < nums1Size && p2 < nums2Size)
        {
            // Return the smaller one
            // Recall that post increment is less efficient because it returns the value before the increment.
            // Therefore, we are really doing return nums1[p1]; p1++, but obviously we cannot increment p1 after the return1
            return nums1[p1] < nums2[p2] ? nums1[p1++] : nums2[p2++];
        }
        else if(p1 < nums1Size)
        {
            return nums1[p1++];
        }
        else if(p2 < nums2Size)
        {
            return nums2[p2++];
        }

        // Should never get here
        assert(0);
        return -1;
    }

    double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        // Need to call getNextFromMerged many times, how many?
        const auto nums1Size = std::ssize(nums1);
        const auto nums2Size = std::ssize(nums2);

        if((nums1Size+nums2Size) & 1)
        {
            // Odd case, so we need to get the middle value.
            auto ret = 0;
            // So I am doing a 0 based approach. E.g. if it's odd, then:
            //  0,1,2,3,4   4/2 = 2 = middle value. Hence I -1 from the total size = nums1Size + nums2Size - 1
            // [1,2,3,4,5]
            const auto middle = (nums1Size + nums2Size - 1)/2;
            for(auto i = 0; i <= middle; ++i)
            {
                ret = getNextFromMerged(nums1,nums2);
            }
            return ret;
        }
        else // This is even, so again we use the 0 based approach since it's easy for my brain to think of it that way
        {
            // We need the middle and middle +1 element, then average them
            const auto middlePlus1 = (nums1Size + nums2Size - 1)/2 + 1;
            auto left = 0;
            auto right = 0;
            for(auto i = 0; i <= middlePlus1; ++i)
            {
                left = right;
                right = getNextFromMerged(nums1,nums2);
            }
            return (left + right)/2.0;
        }
        return -1;
    }
};

class SolutionBinarySearch {
public:
    double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        // Cache the sizes
        const auto nums1Size = std::ssize(nums1);
        const auto nums2Size = std::ssize(nums2);
        const auto N = nums1Size + nums2Size;
        const auto NHalf = N/2;

        const bool isOdd = N&1;

        // We want to run binary search on the smaller array.
        const auto& A = nums1Size > nums2Size ? nums1 : nums2;
        const auto& B = nums1Size <= nums2Size ? nums1 : nums2;

        // Note: WE ARE USING ZERO BASED INDICES HERE!!!
        auto BLeftIndex = decltype(nums1Size){0};
        auto BRightIndex = std::ssize(B) - 1;

        while(BLeftIndex <= BRightIndex)
        {
            // Work out the elements:
            // max_A_left, min_A_right
            // max_B_left, min_B_right
            // In order to do that, I must perform binary search on B:
            
            // BMid is always in the left half.
            const auto BMidIndex = (BLeftIndex + BRightIndex)/2;

            // 
            const auto maxBLeftVal = B[BMidIndex];

            // If we have 1 element, then we have:
            // [1]
            //  L
            //  M
            //  R
            // so take minBRightVal = B[BMidIndex]
            // However, if we have 2 or more elements, then we can take minBRightVal as B[BMidIndex+1]
            const auto minBRightVal = BMidIndex == BRightIndex ? B[BMidIndex] : B[BMidIndex+1];

            // Now work out max_A_left, min_A_right
            // Note that N is 1 based. Thus, to work out how many elements of A I need, I can
            // make BMidIndex one based too before subtracting from NHalf:
            const auto numEleFromA = NHalf - (BMidIndex + 1);
            // Now make it an index
            const auto AMidIndex = numEleFromA - 1; // make it 0 based.

            // If we take no elements from A, we still need to compare with A's values, so we set these sentinel values.
            const auto maxALeftVal = numEleFromA == 0 ? std::numeric_limits<int>::lowest() : A[AMidIndex];
            const auto minARightVal = numEleFromA == 0 ? std::numeric_limits<int>::max() :
            numEleFromA == 1 ? maxALeftVal : A[AMidIndex + 1]; // Just in base both A and B are single element indices.
            
            //auto maxALeftVal = int{};
            //if(numEleFromA == 0)
            //{
            //    maxALeftVal = 
            //}


            // Now I can test the condition
            // If  maxBLeftVal > minARightVal, it means we need less from B and more from A, thus we search to the left of B
            if(maxBLeftVal > minARightVal)
            {
                BRightIndex = BMidIndex - 1;
                continue;
            }
            else if(maxALeftVal > minBRightVal) // We need more from B and less from A. Look to the right of B
            {
                BLeftIndex = BMidIndex + 1;
                continue;
            }

            // Otherwise the condition is satisfied and now we should work out our median!
            if(N % 2 == 0)
            {
                auto  res = double{0};
                if(N/2 == B.size())
                {
                    // We have used up all the elements from B, but we need to do the average with the next element up.
                    // The problem is that we have assigned sentinel values to maxALeftVal.
                    // let's just calculate this case manually.
                    // E.g.
                    // A = [3,4]
                    // B = [1,2]
                    res = (B.back() + A.front()) / 2.0;
                }
                else
                {
                    // If the total number of elements are even, then we need to get the avg of (the largest left, min right):
                    const auto largestLeftVal = std::max(maxALeftVal, maxBLeftVal);
                    const auto minRightVal = std::min(minARightVal, minBRightVal);
                    res = (largestLeftVal + minRightVal) / 2.0;
                }
                return res;
            }
            else
            {
                // For the same reason above, it may be that we have used up all the N/2 elements in B
                // e.g. if
                // A = [3,4,5]
                // B = [1,2]
                // So N/2 +1th element = 5/2 +1 = 3rd element, but that's in A.
                //if(N/2 == B.size())
                //{
                //    return A.front();
                //}
                //else
                {
                    // Note: If the total number of elements is odd, we simply return the 
                    // (N/2 +1)th element. E.g.
                    //
                    // [1,2,3,4,5], 5/2 = 2, 2+1 = 3, return the 3th element, which is min(min_A_R,min_B_R),
                    // i.e. the smaller of the two right halves.
                    const auto minRightVal = std::min(minARightVal, minBRightVal);
                    return minRightVal;
                }
                
            }
        }

        // If we are out of the for loop, then it means we do not take any elements from B. Only A.
        // If even:
        //  0 1 2 3 4 5
        // [1,2,3,4,5,6], get average of two middle element
        if(N % 2 == 0)
        {
            if(N/2 < A.size())
            {
                return (A[N/2 - 1] + A[N/2]) / 2.0;
            }
            else
            {   
                // We need the first value of B to work out the (N/2  +1)'s value, since N/2 is already at the end of A.
                // We might have something like 
                // A = [1,2]
                // B = [3,4]
                // So we need to take the average of 2 and 3
                return (A[N/2] + B[0]) / 2.0;
            }
        }
        else
        {
            // For the same reason above, the N/2+1th value might be in B. So we need to check this:
            if(N/2 < A.size())
            {
                return A.size() == 1 ? A.front() : A[N/2  +1];
            }
            else
            {
                return B[0];
            }
        }
    }
};


//TEST_CASE("Benchmark Fibonacci", "[SolutionBinarySearch]") {
//    auto solutionBinarySearch = SolutionBinarySearch{};
//    REQUIRE(solutionBinarySearch.findMedianSortedArrays({1,3},{2}) == 2);
//
//    //REQUIRE(fibonacci(20) == 6'765);
//    //BENCHMARK("fibonacci 20") {
//    //    return fibonacci(20);
//    //};
////
//    //REQUIRE(fibonacci(25) == 75'025);
//    //BENCHMARK("fibonacci 25") {
//    //    return fibonacci(25);
//    //};
//}

auto main(int argc, char* argv[])->int
{
    //auto ii = SolutionLinear{}.findMedianSortedArrays({1,2},{3,4});

    
    //auto ii = SolutionBinarySearch{}.findMedianSortedArrays({1,3},{2});
    //auto ii = SolutionBinarySearch{}.findMedianSortedArrays({1,2},{3,4});
    //auto ii = SolutionBinarySearch{}.findMedianSortedArrays({},{1});
    //auto ii = SolutionBinarySearch{}.findMedianSortedArrays({},{2,3});
    auto ii = SolutionBinarySearch{}.findMedianSortedArrays({3},{-2,-1});// I give up. I'll do this on the weekend.
    auto iii = 42;
    return 0;
}

