//struct Coordinates
//{
//    int row{};
//    int col{};
//
//    constexpr auto operator<=>(const Coordinates&) const = default;
//};

// This is wrong, I'll need to come back and re-do it.
// I used this solution: https://leetcode.com/problems/word-search/solutions/4965052/96-45-easy-solution-with-explanation/
// I need to understand it, but ATM I am busy trying to get a grasp on system design first


#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <utility>

//#include "../common/catch_amalgamated.hpp"

// Note: This solution works, but the hash function is slow and making it time out
// for large test cases
class Solution {
public:
    bool exist(const std::vector<std::vector<char>>& board, const std::string& word)
    {
        // We search in all four directions, matching the letters in "word". 
        // If we have reached i = std::size(word), it means that all the previous entries 0, .. size-1 matches, 
        // and so we have found the word.

        const auto& wordSize = std::ssize(word);
        const auto& boardRowSize = board.size();
        const auto& boardColSize = board[0].size();

        auto pairHash = [](const std::pair<int,int>& p){
            auto seed = p.first + p.second;

            auto hasher = std::hash<int>{};
            seed ^= hasher(p.first) + 0x9e3779b9 + (seed << 6) + (seed >>2);
            seed ^= hasher(p.second) + 0x9e3779b9 + (seed << 6) + (seed >>2);
            return seed;
        };
        auto visited = std::unordered_set<std::pair<int,int>, decltype(pairHash)>{};

        auto backtrack = [&](auto&& backtrack, int rowi, int colj, int wordi)
        {
            // We have previously considered all the letters 0..size-1, so we can return true.
            if(wordi == wordSize)
            {
                return true;
            }

            // Have we gone out of bounds (but still haven't finished find the word) or if this has already been visited?
            // we can think of these as the physical walls bounding us, yes, a visited square is a wall. Think of the game snake.
            if(rowi < 0 || colj < 0 || rowi >=boardRowSize || colj >= boardColSize || visited.contains({rowi, colj}))
            {
                return false;
            }
            // If the letter is incorrect, return false;
            if(board[rowi][colj] != word[wordi])
            {
                return false;
            }

            // We now know that this is a valid square to visit, and the letter in this square matches what's in word.
            // So we can mark this square as visited and advance in all four directions.

            visited.insert({rowi,colj});

            const auto nextLetter = wordi+1;
            auto exists = backtrack(backtrack,rowi + 1, colj, nextLetter) || // up 
                          backtrack(backtrack,rowi - 1, colj, nextLetter) || // down
                          backtrack(backtrack,rowi, colj + 1, nextLetter) || // right
                          backtrack(backtrack,rowi, colj - 1, nextLetter);   // left

            // If exists is true, it means that the end of the word is reachable from this square, so we return true.
            if(exists) return true;

            // Otherwise, we have to backtrack by un-visiting this square
            visited.erase({rowi,colj});

            return false;
        };

        // calling backtrack(0,0) will start the search from 0,0, but we need to search starting from all squares
        for(auto i = 0; i < boardRowSize; ++i)
        {
            for(auto j = 0; j < boardColSize; ++j)
            {
                if(backtrack(backtrack, i,j, 0))
                {
                    return true;
                }
            }
        }
        

        return false;
    }
};

// This passes all test cases
class SolutionNoHash {
public:
    bool exist(std::vector<std::vector<char>>& board, const std::string& word)
    {
        // We search in all four directions, matching the letters in "word". 
        // If we have reached i = std::size(word), it means that all the previous entries 0, .. size-1 matches, 
        // and so we have found the word.

        const auto& wordSize = std::ssize(word);
        const auto& boardRowSize = board.size();
        const auto& boardColSize = board[0].size();

        auto backtrack = [&](auto&& backtrack, int rowi, int colj, int wordi)
        {
            // We have previously considered all the letters 0..size-1, so we can return true.
            if(wordi == wordSize)
            {
                return true;
            }

            // Have we gone out of bounds (but still haven't finished find the word) or if this has already been visited?
            // we can think of these as the physical walls bounding us, yes, a visited square is a wall. Think of the game snake.
            if(rowi < 0 || colj < 0 || rowi >=boardRowSize || colj >= boardColSize)
            {
                return false;
            }
            // If the letter is incorrect, return false;
            if(board[rowi][colj] != word[wordi])
            {
                return false;
            }

            // We now know that this is a valid square to visit, and the letter in this square matches what's in word.
            // So we can mark this square as visited and advance in all four directions.

            auto temp = board[rowi][colj];

            board[rowi][colj] = '\n';

            const auto nextLetter = wordi+1;
            auto exists = backtrack(backtrack,rowi + 1, colj, nextLetter) || // up 
                          backtrack(backtrack,rowi - 1, colj, nextLetter) || // down
                          backtrack(backtrack,rowi, colj + 1, nextLetter) || // right
                          backtrack(backtrack,rowi, colj - 1, nextLetter);   // left

            // If exists is true, it means that the end of the word is reachable from this square, so we return true.
            if(exists) return true;

            // Otherwise, we have to backtrack by un-visiting this square
            board[rowi][colj] = temp;

            return false;
        };

        // calling backtrack(0,0) will start the search from 0,0, but we need to search starting from all squares
        for(auto i = 0; i < boardRowSize; ++i)
        {
            for(auto j = 0; j < boardColSize; ++j)
            {
                if(backtrack(backtrack, i,j, 0))
                {
                    return true;
                }
            }
        }
        

        return false;
    }
};


auto main(int argc, char* argv) -> int
{
    auto ss = std::vector<std::vector<char>>{
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    //auto ss = std::vector<std::vector<char>>{
    //    {'A','B'},
    //};
    auto sss = Solution{}.exist(ss,"ABCCED");
    return 0;
}

