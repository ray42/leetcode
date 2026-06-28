#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Solution14 {
public:
    std::string longestCommonPrefix(const std::vector<std::string>& strs)const {

        // 1 <= strs.length <= 200, so if there is only one string, then it is the longest common prefix.
        if (strs.size() == 1) {
            return strs[0];
        }

        // Find the minimum length string in the array
        auto minLength = strs[0].size();
        for (const auto& str : strs) {
            minLength = std::min(minLength, str.size());
        }

        // Check each character position
        for (auto i = size_t{}; i < minLength; ++i) {
            auto currentChar = strs[0][i];

            for (std::size_t j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != currentChar) {

                    // This works because if the characters at position i 
                    // are not the same, then the longest common prefix 
                    // must end before this position.
                    // and i starts from 0 and substr's second parameter is 
                    // the length of the substring, so it will return the 
                    // substring from index 0 to index i-1.
                    return strs[0].substr(0, i);
                }
            }
        }

        return strs[0].substr(0, minLength);
    }
};

// This is a cool solution too.
class Solution14_2 {
public:
    std::string longestCommonPrefix(std::vector<std::string>& v) {
        std::string ans = "";
        sort(v.begin(), v.end());
        int n = v.size();
        std::string first = v[0], last = v[n - 1];
        for (int i = 0; i < std::min(first.size(), last.size()); i++) {
            if (first[i] != last[i]) {
                return ans;
            }
            ans += first[i];
        }
        return ans;
    }
};
