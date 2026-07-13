#include <gtest/gtest.h>
#include "00071_SimplifyPath.hpp"

TEST(SimplifyPath, Placeholder) {
    // TODO: Add test cases for Solution71
  auto solution = Solution71{};
  auto home = std::string{ "/home/" };
  auto result = solution.simplifyPath(home);
  EXPECT_EQ(result, "/home");
}
