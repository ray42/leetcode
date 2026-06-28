#include <gtest/gtest.h>
#include <algorithm>
#include "00049_GroupAnagrams.hpp"

// Helper to sort the result for comparison (order doesn't matter)
static auto sortedResult(std::vector<std::vector<std::string>> result) {
    for (auto& group : result) {
        std::sort(group.begin(), group.end());
    }
    std::sort(result.begin(), result.end());
    return result;
}

TEST(GroupAnagrams, BasicCase) {
    Solution49 sol;

    auto input = std::vector<std::string>{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto result = sortedResult(sol.groupAnagrams(input));

    auto expected = sortedResult({
        {"ate", "eat", "tea"},
        {"nat", "tan"},
        {"bat"}
    });

    EXPECT_EQ(result, expected);
}

TEST(GroupAnagrams, EmptyString) {
    Solution49 sol;

    auto input = std::vector<std::string>{""};
    auto result = sol.groupAnagrams(input);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], std::vector<std::string>{""});
}

TEST(GroupAnagrams, SingleChar) {
    Solution49 sol;

    auto input = std::vector<std::string>{"a"};
    auto result = sol.groupAnagrams(input);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], std::vector<std::string>{"a"});
}
