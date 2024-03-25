#include <vector>


/*
                     1     2     3     4      5
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]

Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

*/

class Solution {
public:
    auto insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) -> std::vector<std::vector<int>>
    {
        // How to do this? Well, we first find out where to insert it.
        auto i = 0;
        while(i < intervals.size() && intervals[i][0] < newInterval[0])
        {
            ++i;
        }

        // Now we need to compare newInterval[0] with intervals[i-1][1] to see if we need to merge.
        // An exception is if i = 0, this means we can insert at the beginning.
        // If i = intervals.size(), then we can just insert at the end.
        

        // Then we compare the start of newInterval with the end of the index previous to it.
        // If newInterval happens to be inserted at 
        //

        for(auto i = 0; i < intervals.size(); ++i)
        {
            //if(intervals[i][0])
        }
    }
};

