/*
EASY: https://leetcode.com/problems/transpose-matrix/

Given a 2D integer array matrix, return the transpose of matrix.

The transpose of a matrix is the matrix flipped over its main diagonal, 
switching the matrix's row and column indices.

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]

Example 2:

Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]

*/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using MatType = std::vector<std::vector<int>>;
auto toStr(const MatType& matrix) -> std::string
{
    auto ss = std::stringstream{};
    ss << '[';
    for(const auto& rowI : matrix)
    {
        ss << '[';
        for(const auto& columnJ : rowI)
        {
            ss << columnJ << ' ';
        }
        ss << ']';
    }
    ss << ']';
    return ss.str();
}

class Solution {
public:
    auto transpose(const MatType& matrix) -> MatType
    {
        const auto rowSize = matrix.size();
        const auto colSize = matrix[0].size();
        auto ret = MatType{colSize, std::vector<int>(rowSize,0)};

        for(auto rowi = 0; rowi < rowSize; ++rowi)
        {
            for(auto coli = 0; coli < colSize; ++coli)
            {
                ret[coli][rowi] = matrix[rowi][coli];
            }
        }
        return ret;
    }
};

auto main(int argc, char * argv[]) -> int
{
    auto mat = MatType{};
    mat.push_back({1,2,3});
    mat.push_back({4,5,6});
    mat.push_back({7,8,9});
    std::cout << toStr(mat) << std::endl;
    std::cout << toStr(Solution{}.transpose(mat)) << std::endl;
    return 0;
}
