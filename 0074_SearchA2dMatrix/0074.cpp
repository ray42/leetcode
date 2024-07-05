/*
This builds on the binary search algorithm where we find a final x in a sorted array arr.
We do this by:
1) Look at the middle of the array, 
       if it's lower, then we search in the left part of the array
       if it's higher then we search in the right part of the array.

        auto lo = static_cast<int>(0);
        auto hi = static_cast<int>(nums.size()-1);
        auto mid = static_cast<int>(-1);
        while(lo <= hi)
        {
            mid = (lo + hi) / 2;

            if(target > nums[mid])
            {
                lo = mid + 1;
            }
            else if(target < nums[mid])
            {
                hi = mid - 1;
            }
            else
            {
                return mid;
            }
            
        }

However, the difficulty here is that we search in a matrix. This means we have to convert the "middle" into row and column indices.
How to do this?
  |0 |1 |2 |3
----------------
0 |0 |1 |2 |3
----------------
1 |4 |5 |6 |7
----------------
2 |8 |9 |10|11

So we know we can take lo = 0, and high = nrow * ncol - 1 = 3*4-1

Given an element, say 5, then the formula for 5 is:
5 = i * ncol + j

So, given 5, how do we find i and j?
i = floor(5/ncol)
j = 5 - i * ncol

Now we can use this in the normal binary search algorithm.
*/
#include <vector>


class Solution {
public:
    auto searchMatrix(const std::vector<std::vector<int>>& matrix, const int target) -> bool
    {
        const auto nRows = static_cast<int>(matrix.size());
        const auto nCols = static_cast<int>(matrix[0].size());
        auto lo = static_cast<int>(0);
        auto hi = static_cast<int>(nRows * nCols - 1);
        auto mid = static_cast<int>(-1);
        auto rowi = static_cast<int>(-1);
        auto colj = static_cast<int>(-1);

        while(lo <= hi)
        {
            mid = (lo + hi) / 2;
            
            rowi = mid/nCols;
            colj = mid - rowi * nCols;

            if(target < matrix[rowi][colj])
            {
                hi = mid-1;
            }
            else if(target > matrix[rowi][colj])
            {
                lo = mid+1;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};

auto main(int argc, char* argv[]) -> int
{
    auto iii = Solution{}.searchMatrix({{1,3,5,7},{10,11,16,20},{23,30,34,60}},3);
    return 0;
}

