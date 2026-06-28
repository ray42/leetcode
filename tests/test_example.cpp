#include <gtest/gtest.h>
#include "00001_TwoSum.hpp"

TEST(TwoSum, BasicCase) {
    Solution1 sol;

    auto nums = std::vector<int>{2, 7, 11, 15};
    auto result = sol.twoSum(nums, 9);

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

TEST(TwoSum, TargetInMiddle) {
    Solution1 sol;

    auto nums = std::vector<int>{3, 2, 4};
    auto result = sol.twoSum(nums, 6);

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
}
