# LeetCode Solutions - Project Structure

## Folder Layout

```
src/
├── solution.slnx                    # Visual Studio solution (both projects)
├── LeetCode/
│   ├── LeetCode.vcxproj            # Main project
│   ├── LeetCode.cpp                # Entry point - includes all solution headers
│   ├── common_types.hpp            # Shared types (TreeNode, ListNode)
│   └── 0*.hpp                      # Solution headers (header-only classes)
└── LeetCodeTests/
    ├── LeetCodeTests.vcxproj       # Test project (links gtest via vcpkg)
    ├── tests_main.cpp              # Google Test entry point
    └── test_*.cpp                  # Test files
```

## Projects

| Project | Purpose | Output |
|---------|---------|--------|
| `LeetCode` | Compiles all solution headers via `LeetCode.cpp` | `LeetCode.exe` |
| `LeetCodeTests` | Unit tests using Google Test | `LeetCodeTests.exe` |

Solutions are header-only `.hpp` files. They are compiled because `LeetCode.cpp` includes all of them. The test project includes individual solution headers as needed.

## How Google Test Works in Visual Studio

- The `LeetCodeTests` project builds an executable that runs all tests.
- Visual Studio's **Test Explorer** (Test → Test Explorer) auto-discovers gtest tests and shows them in a tree view. You can run or debug individual tests from there.
- The test project references solution headers via include path (`../LeetCode`).
- Gtest headers and libraries come from vcpkg (triplet: `x64-win-utc`).
- `tests_main.cpp` provides the `main()` function that initializes and runs Google Test.

## Adding a New Test File

1. Create `src/LeetCodeTests/test_<name>.cpp`:

```cpp
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
```

2. Add the file to `LeetCodeTests.vcxproj` under the `<ItemGroup>` containing `<ClCompile>` entries:

```xml
<ClCompile Include="test_<name>.cpp" />
```

3. Optionally add to `LeetCodeTests.vcxproj.filters` to keep it organized in Solution Explorer.

## Adding a New Solution

1. Create `src/LeetCode/NNNNN_ProblemName.hpp` with `#pragma once` at the top.
2. Name the class `SolutionNNNNN` (use the problem number as suffix).
3. If the solution uses `TreeNode` or `ListNode`, add `#include "common_types.hpp"`.
4. Add `#include "NNNNN_ProblemName.hpp"` to `LeetCode.cpp`.
5. Add a `<ClInclude>` entry to `LeetCode.vcxproj` and `LeetCode.vcxproj.filters`.

## Building on Linux

From the repo root:

```bash
chmod +x build.sh
./build.sh        # Debug build (default)
./build.sh Release
```

This uses CMake with Google Test fetched automatically via `FetchContent`. No vcpkg needed on Linux.
