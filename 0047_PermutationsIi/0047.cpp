
#include <vector>
#include <unordered_set>

// When doing this again, try both this way and Neetcode's video's way.
class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        
        auto result = std::vector<std::vector<int>>{};
        auto dfs = [&](auto&& dfs, int idx)
        {
            // We don't need to swap the last number at the N-1th position
            // (since the only choice left is to swap it with itself)
            if(idx == std::ssize(nums)-1)
            {
                result.push_back(nums);
                return;
            }
            auto uset = std::unordered_set<int>{};

            for(auto i = idx; i < std::ssize(nums); ++i)
            {
                if(uset.contains(nums[i]))
                {
                    continue;
                }

                uset.insert(nums[i]);
                std::swap(nums[idx], nums[i]);
                dfs(dfs,idx+1);
                std::swap(nums[i], nums[idx]);
            }
        };

        dfs(dfs,0);

        return result;
    }
};

class SolutionHashMap {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        
        auto result = std::vector<std::vector<int>>{};
        auto dfs = [&](auto&& dfs, int idx)
        {
            // We don't need to swap the last number at the N-1th position
            // (since the only choice left is to swap it with itself)
            if(idx == std::ssize(nums)-1)
            {
                result.push_back(nums);
                return;
            }
            auto uset = std::unordered_set<int>{};

            for(auto i = idx; i < std::ssize(nums); ++i)
            {
                if(uset.contains(nums[i]))
                {
                    continue;
                }

                uset.insert(nums[i]);
                std::swap(nums[idx], nums[i]);
                dfs(dfs,idx+1);
                std::swap(nums[i], nums[idx]);
            }
        };

        dfs(dfs,0);

        return result;
    }
};

auto main(int argc, char* argv[]) -> int
{

}

