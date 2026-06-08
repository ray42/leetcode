/*
MEDIUM https://leetcode.com/problems/longest-consecutive-sequence/description/

RayNotes:

1 Solved using Array(Three Nested Loop). Brute Force Approach.
2 Solved using Array + Sorting. Brute Better Approach.
3 Solved using Array + Hash Table(Unordered map). Optimize Approach.
4 Solved using Array + Hash Table (Unordered set). Optimize Approach.
*/

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iterator>

// 1 Solved using Array(Three Nested Loop). Brute Force Approach.
class Solution1 {
public:

    // We loop through nums[i], i = [0,nums.size()) and work out the longest consecutive sequence starting at each nums[i]
    auto longestConsecutive(const std::vector<int>& nums) -> int
    {
        auto maxLength = 0;
        for(const auto n : nums) // O(N)
        {
            // Now find if n+1, n+2, etc... is in nums
            auto nextNum = n+1;
            auto currentLength = 1;
            while(std::ranges::find(nums, nextNum) != nums.end()) // O(N)*O(N) the while itself is O(N) and the find itself is O(N) (linear search)
            {
                ++nextNum;
                ++currentLength;
            }
            maxLength = std::max(currentLength, maxLength);
        }

        return maxLength;
    }
};


// 2 Solved using Array + Sorting. Brute Better Approach.
class Solution2 {
public:

    // Sort, then go through checking for consecutive sequence.
    auto longestConsecutive(std::vector<int>& nums) -> int
    {
        std::ranges::sort(nums); // O(NlogN)
        
        const auto numsSize = nums.size();
        if(numsSize == 0) return 0;

        auto maxLength = 1;
        auto currentLength = 1;
        for(auto i = 1; i < numsSize; ++i) // O(N)
        {
            if(nums[i-1] == nums[i]) continue; // skip repeated numbers

            if(nums[i-1] + 1 == nums[i])
            {
                ++currentLength;
            }
            else
            {
                maxLength = std::max(maxLength, currentLength);

                // Reset the current length to 1
                currentLength = 1;
            }
        }

        // We need to do this in case the longest sequence is at the END of the sorted nums.
        // If it's at the end, it means that we do not have one more entry at the end of nums
        // for us to go into the else statement.
        return std::max(maxLength, currentLength); 
    }
};


// 3 Solved using Array + Hash Table(Unordered map). Optimize Approach.
// We use a hash table to help us identify WHERE to start counting from. That is, where is the start of a sequence.
// and we can use the same hash table to check if the next number in the sequence is present or not.
class Solution3 {
public:
    auto longestConsecutive(std::vector<int>& nums) -> int
    {
        if(nums.empty()) return 0;

        auto um = std::unordered_map<int, bool>{};
        
        // Insert all nums into um
        for(const auto n : nums)
        {
            um[n] = false;
        }

        // Set the sequence start to true
        for(auto& [n, isSequenceStart] : um)
        {
            // If the previous number is not in the hash map, then this is the start of a sequence.
            if(!um.contains(n-1)) isSequenceStart = true;
        }

        auto maxLength = 1;
        // Now loop through the sequence starts and check if the increasing consecutive numbers are in the map
        for(const auto& [n, isSequenceStart] : um)
        {
            if(isSequenceStart)
            {
                auto currentMaxLength = 1;
                auto nextInSequence = n+1;
                while(um.contains(nextInSequence))
                {
                    ++currentMaxLength;
                    ++nextInSequence;
                }
                maxLength = std::max(currentMaxLength, maxLength);
            }
        }

        return maxLength;
    }
};


// 4 Solved using Array + Hash Table (Unordered set). Optimize Approach.
// This is very similar to the one above. However, in the one above, we use three loops. We can combine the last two loops
class Solution4 {
public:
    auto longestConsecutive(std::vector<int>& nums) -> int
    {
        if(nums.empty()) return 0;

        auto numsSet = std::unordered_set<int>(std::make_move_iterator(nums.begin()), std::make_move_iterator(nums.end()));

        auto maxLength = 1;
        for(const auto n : numsSet)
        {
            // Is this a start of a sequence? If it isn't, then just continue
            if(numsSet.contains(n-1)) continue;

            // Otherwise we have the start of a sequence.
            auto currentMaxLength = 1;
            auto nextInSequence = n+1;
            while(numsSet.contains(nextInSequence))
            {
                ++currentMaxLength;
                ++nextInSequence;
            }

            maxLength = std::max(currentMaxLength, maxLength);
        }

        return maxLength;
    }
};




auto main(int argc, char* argv[]) -> int
{
    auto ss = std::vector<int>{100,4,200,1,3,2}; // 0,3,7,2,5,8,4,6,0,1
    auto sss = std::vector<int>{0,3,7,2,5,8,4,6,0,1};  
    Solution2{}.longestConsecutive(sss);
    return 0;
}




