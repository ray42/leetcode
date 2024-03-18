#include <vector>


/*

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

How to do this? Well, we first find out where to insert it.
Then we compare the start of newInterval with the end of the index previous to it.
If newInterval happens to be inserted at 

*/

class Solution {
public:
    auto insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) -> std::vector<std::vector<int>>
    {
        // First find where does the new interval fit in
        for(auto i = 0; i < intervals.size(); ++i)
        {
            //if(intervals[i][0])
        }
    }
};

