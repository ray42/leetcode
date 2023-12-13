/*
EASY 1582. Special Positions in a Binary Matrix
https://leetcode.com/problems/special-positions-in-a-binary-matrix/

Given an m x n binary matrix mat, return the number of special positions in mat.

A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).

Example 1:

Input: mat = [[1,0,0],
              [0,0,1],
              [1,0,0]]
Output: 1
Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.

Example 2:

Input: mat = [[1,0,0],
              [0,1,0],
              [0,0,1]]
Output: 3
Explanation: (0, 0), (1, 1) and (2, 2) are special positions.

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 100
    mat[i][j] is either 0 or 1.

Intuition

To find the special positions in the binary matrix, 
we need to iterate through each row and column and check if the current position (i, j) is special. 
A position is considered special if the element at that position is 1, 
and all other elements in its row and column are 0.

Approach

    1) Iterate through each row of the matrix.
    2) For each row, check if there is exactly one element with the value 1. If found, remember its column index.
    3) After scanning the row, check the corresponding column for the remembered index. If the element is 1 and there are no other 1s in that column, it's a special position.
    4) Repeat this process for all rows.
    5) Count and return the number of special positions.

Complexity

    Time Complexity: O(m * n), where m is the number of rows and n is the number of columns in the matrix.

    Space Complexity: O(1) as we use constant space.

Improvement:
   In step (2) when we are scanning through the row, if we find more than one 1s, then we can discount (remember not to scan) those columns ever again.
   This is because the row is discounted and any 1s found on the row, the corresponding column cannot contain a 1 elsewhere to make it special.
   In fact, we can always discount the column containing 1 on this row, because containing 1 anywhere else will make the column not special.

   In step (3) when we are scanning the column, two are three outcomes:
   *) The column has zero 1s. This cannot happen, since we know it contains one 1s.
   1) The column has one 1s (at the position of where the row is). This means that this column cannot be special for a different row, 
      so we can remember to not scan it again.
   2) The column contains more than one 1s, we can remember to not scan this column again.

   This means, we can always eliminate a column when we find a 1 on the row.
*/

#include <vector>
#include <unordered_set>

using MatType = std::vector<std::vector<int>>;
class Solution 
{
public:

    int numSpecial(const MatType& mat) 
    {
        auto discountedColumns = std::unordered_set<int>{};
        auto discountedRows = std::unordered_set<int>{};
        auto numSpecials = 0;
        for(auto rowi = 0; rowi < mat.size(); ++rowi)
        {
            if(discountedRows.contains(rowi)) continue;

            auto maybeSpecialColi = checkRow(mat, rowi, discountedColumns);

            if(maybeSpecialColi >= 0 && checkColumn(mat, rowi, maybeSpecialColi, discountedRows))
                ++numSpecials;
        }

        return numSpecials;
    }

private:

    // Returns the index of the column if there is exactly one 1s on this row.
    // Otherwise, return -1 if there is more than one 1s or no 1s
    // Inserts the column indices of all 1s in discountedColumns
    auto checkRow(const MatType& mat, const int rowi, std::unordered_set<int>& discountedColumns) -> int
    {
        auto columnIndex = int{-1};
        auto moreThanOneOne = false;
        for(auto coli = 0; coli < mat[0].size(); ++coli)
        {
            if(discountedColumns.contains(coli)) continue;

            if(mat[rowi][coli] == 1)
            {
                discountedColumns.insert(coli);
                if(columnIndex >= 0) // A 1 has been found previously.
                {
                    moreThanOneOne = true;
                }
                else
                {
                    columnIndex = coli;
                }
            }
        }
        return moreThanOneOne ? -1 : columnIndex;
    }

    auto checkColumn(const MatType& mat, int rowIBeingChecked, const int maybeSpecialColi, std::unordered_set<int>& discountedRows) -> bool
    {
        auto isSpecial = bool{true};
        for(auto rowi = 0; rowi < mat.size(); ++rowi)
        {
            if(mat[rowi][maybeSpecialColi] == 1 && rowi != rowIBeingChecked) // We have found another 1 in this column!
            {
                discountedRows.insert(rowi);
                isSpecial = false;
            }
        }

        return isSpecial;
    }
};


auto main(int argc, char * argv[]) -> int
{

    return 0;
}
