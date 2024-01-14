/*
MEDIUM https://leetcode.com/problems/valid-sudoku/

Ray Notes:

Brute Force Approach:

Have a set, 
1) loop through all rows and make sure all digits in there are not in the set (uniqueness check).
2) loop through all cols and make sure all digits in there are not in the set (uniqueness check).
3) loop through all 9 sub grids and make sure all digits in there are not in the set (uniqueness check).
     To Loop through the sub-grids, we have to do something like:
       |0 1 2 | 3 4 5 | 6 7 8
      -|------|-------|------
      0|      |       |      
      1|      |       |      
      2|      |       |      
      -|------|-------|------
      3|      |       |      
      4|      |       |      
      5|      |       |      
      -|------|-------|------
      6|      |       |      
      7|      |       |      
      8|      |       |      
     
     So: 
     top left we loop i = 0..2, j = 0..2
     top middle:      i = 0..2, j = 3..5
     etc...
     This means we have to write 9 loops.

     HOWEVER, note that we have looped through all the values THREE times.

Single Pass Approach

     We can do better. Let's loop through all the values once.
     Say we are at val_{i,j}, 
       this means we need to check if val has been seen already in row i
       this means we need to check if val has been seen already in col j
       this means we need to check if val has been seen already in subgrid k = i/3*3 + j/3

       How did we come up with the formula for k? Well, there are 9 subgrids 0..8.
       We need to map each val_{i,j} onto one of the sub-grids. 
       From the values of K in the grid:

        0 1 2 | 3 4 5 | 6 7 8
       ----------------------
      0|0 0 0 | 1 1 1 | 2 2 2
      1|0 0 0 | 1 1 1 | 2 2 2
      2|0 0 0 | 1 1 1 | 2 2 2
      -|------|-------|------
      3|3 3 3 | 4 4 4 | 5 5 5
      4|3 3 3 | 4 4 4 | 5 5 5
      5|3 3 3 | 4 4 4 | 5 5 5
      -|------|-------|------
      6|6 6 6 | 7 7 7 | 8 8 8
      7|6 6 6 | 7 7 7 | 8 8 8
      8|6 6 6 | 7 7 7 | 8 8 8

     We need column j =0..8 to be mapped to 0..2, this can be done by diving by 3:
       (0,1,2)/3 = 0, (3,4,5)/3 = 1, (6,7,8)/3 = 2.
    For the row offset, we know that we can get 0,1,2, but we really need 0,3,6 (the start of each row)
       That is, we can simply multiply 3.

    OK, so now that we have all the indices sorted out, how do we actually do the checking? We could use lots of unordered_sets.
    That is, we have:
    auto colSets = std::vector<std::unordered_map<int>>(9); // size 9
    auto rowSets = std::vector<std::unordered_map<int>>(9); // size 9
    auto gridSets = std::vector<std::unordered_map<int>>(9); // size 9

    However, an unordered_map is quite heavy when we know that we only have numbers 0-8. How about, instead of having 9 unordered_maps, we have 9 arrays of bools.
    Each time we see a value, we just set the index of the array to true. This gives:
    bool cols[9][9] = {0};
    bool rows[9][9] = {0};
    bool subgrids[9][9] {0};

    or if we want to use std::arrays, we have:
    auto cols = std::array<std::array<bool,9>,9>{}; // default initialised to false;
    auto rows = std::array<std::array<bool,9>,9>{}; // default initialised to false;
    auto subgrids = std::array<std::array<bool,9>,9>{}; // default initialised to false;
*/

#include <vector>
#include <array>

class Solution {
public:
    auto isValidSudoku(const std::vector<std::vector<char>>& board) -> bool
    {
        bool rows[9][9] = {0};
        bool cols[9][9] = {0};
        bool subgrid[9][9] = {0};
        
        for(auto rowi = 0; rowi < 9; ++rowi)
        {
            for(auto colj = 0; colj < 9; ++colj)
            {
                if(board[rowi][colj] != '.')
                {
                    // Calculate the subgrid number
                    auto subgridk = rowi/3*3 + colj/3;

                    // board[rowi][colj] is a number 1 - 9, we need to convert this to 0 to 8, hence -1
                    auto num = board[rowi][colj] - '0' - 1;

                    // Has it been seen before? - remember that we are using arrays to check if we have seen this before.
                    if(rows[rowi][num] || cols[colj][num] || subgrid[subgridk][num])
                    {
                        return false;
                    }

                    // Update the array to say that we have seen it before
                    rows[rowi][num] = true;
                    cols[colj][num] = true;
                    subgrid[subgridk][num] = true;
                }
            }
        }
        return true;
    }
};






// Re-trying. If I want to re-try again, then use this one
class SolutionRetry {
public:
    auto isValidSudoku(const std::vector<std::vector<char>>& board) -> bool
    {
        // So really, we need to check each row if there are dupes
        //                                  column if there are dupes
        //                                  subgrid if there are dupes

        // We can use a 2D array for each of the above.
        auto rowSeen = std::array<std::array<bool,9>,9>{};
        auto colSeen = std::array<std::array<bool,9>,9>{};
        auto gridSeen = std::array<std::array<bool,9>,9>{};

        // Now loop through the grid and check if any values have seen doubly
        for(auto rowi = 0; rowi < board.size(); ++rowi)
        {
            for(auto colj = 0; colj < board[0].size(); ++colj)
            {
                if(board[rowi][colj] != '.')
                {
                    // Which number are we trying to check for dupes?
                    auto num = board[rowi][colj] - '1'; // This will make it 0 based.

                    // How do we index the subgrid?
                    auto gridk = (rowi/3)*3 + colj/3;

                    if(rowSeen[rowi][num] || colSeen[colj][num] || gridSeen[gridk][num])
                    {
                        return false;
                    }

                    rowSeen[rowi][num] = true;
                    colSeen[colj][num] = true;
                    gridSeen[gridk][num] = true;
                }
            }
        }

        return true;
    }
};




























auto main(int argc, char * argv[]) -> int
{
    return 0;
}
