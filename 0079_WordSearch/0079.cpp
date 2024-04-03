#include <vector>
#include <string>
#include <set>


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
class Solution {
public:
    auto exist(const std::vector<std::vector<char>>& board, const std::string& word) -> bool
    {
        auto visited = std::set<std::pair<int,int>>{};
        auto isExist = dfs(board,word,0,0,0,visited);
        return isExist;
    }

    auto dfs(
        const std::vector<std::vector<char>>& board, 
        const std::string& word, 
        int i, // with letter
        int r, int c, 
        std::set<std::pair<int,int>>& visited) -> bool
    {
        const int nRows = board.size();
        const int nCols = board[0].size();
        if(std::min(r,c) < 0 ||
           r == nRows || c == nCols ||
           visited.contains({r,c})
           )
        {
            return false;
        }

        if(i == word.size()-1) // We are at the end of our word
        {
            if(board[r][c] == word[i])
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // Otherwise, keep on tracking

        visited.emplace(r,c);

        // If the current letter on the board matches the letter in word, then we want to check the next letter.
        if(board[r][c] == word[i]) ++i;

        auto exists = false;

        exists |= dfs(board,word,i,r+1,c,visited);
        exists |= dfs(board,word,i,r-1,c,visited);
        exists |= dfs(board,word,i,r,c+1,visited);
        exists |= dfs(board,word,i,r,c-1,visited);

        visited.erase({r,c});

        return exists;

    }
};


auto main(int argc, char* argv) -> int
{
    //auto ss = std::vector<std::vector<char>>{
    //    {'A','B','C','E'},
    //    {'S','F','C','S'},
    //    {'A','D','E','E'}
    //};

    auto ss = std::vector<std::vector<char>>{
        {'A','B'},
    };
    auto sss = Solution{}.exist(ss,"BA");
    return 0;
}

