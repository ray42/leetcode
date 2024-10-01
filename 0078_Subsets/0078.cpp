/*
How will we do this intuitively? Let the nums be: [1,2,3]
Let's build up a single subset by visiting each number and decide if we include it or not.
E.g.:
1 - should we include 1 or not?
2 - should we include 2 or not?
3 - should we include 3 or not?

^ The choices builds a subset.

We can visualise all the possibilities in a decision tree:

                     1
                  /     \
            [1]  /       \  []
                2         2
         [1,2] / \[1][2] / \ []
              /   \     /   \
             3     3   3     3
            / \   / \ / \   / \
                       [2][3] []
                      [2,3]

No space to write the whole diagram, but you know what I mean.

So, the algorithm is:
1) Traverse the tree in a DFS manner.
2) Keep a currentSubset where we build the subset at each level (adding a new number at each level)
3) Base Case: When the levels reaches the length of nums, we know that we have considered all numbers and we can push the current 

So, we will need:
nums - the input
currSubset - keeps track of the current subset, this will be doing the backtracking
subsets - all of the subsets
level - the level of the tree we are at.

Let's code it up!!!
*/


#include <vector>

/*
Time: There are 2^n possibilities (for each i in n, we have two choices)
      Then we have to copy the currentSubset into allSubsets, which is O(n)
      Total: O(n* 2^n)

Space: O(n)
*/
class Solution {
public:
    auto subsets(std::vector<int>& nums) -> std::vector<std::vector<int>>
    {
        auto currentSubset = std::vector<int>{};
        auto allSubsets = std::vector<std::vector<int>>{};

        auto backtrack = [](
            auto&& backtrack, 
            const std::vector<int>& nums, 
            const int level, 
            std::vector<std::vector<int>>& allSubsets, 
            std::vector<int>& currentSubset)
        {
            if(level == std::ssize(nums))
            {
                allSubsets.push_back(currentSubset);
                return ;
            }

            currentSubset.push_back(nums[level]);
            backtrack(backtrack, nums, level + 1, allSubsets, currentSubset);
            currentSubset.pop_back();
            
            backtrack(backtrack, nums, level + 1, allSubsets, currentSubset);
        };

        backtrack(backtrack, nums, 0, allSubsets, currentSubset);

        return allSubsets;
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}
