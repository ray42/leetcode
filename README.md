# LeetCode Solutions

C++20 solutions to LeetCode problems. Solutions are header-only classes in `src/LeetCode/` — browse them directly. Files are named `NNNNN_ProblemName.hpp` with class `SolutionNNNNN`.

## Folder Layout

```
.
├── CMakeLists.txt                       # CMake build (Linux / CLion / CI)
├── build.sh                             # Linux build script
├── src/
│   ├── solution.slnx                    # Visual Studio solution (both projects)
│   ├── LeetCode/
│   │   ├── LeetCode.vcxproj            # Main project
│   │   ├── LeetCode.cpp                # Entry point - includes all solution headers
│   │   ├── common_types.hpp            # Shared types (TreeNode, ListNode)
│   │   └── 0*.hpp                      # Solution headers (header-only classes)
│   └── LeetCodeTests/
│       ├── LeetCodeTests.vcxproj       # Test project (links gtest via vcpkg)
│       ├── tests_main.cpp              # Google Test entry point
│       └── NNNNN_*Tests.cpp            # Test files
```

## Projects

| Project | Purpose | Output |
|---------|---------|--------|
| `LeetCode` | Compiles all solution headers via `LeetCode.cpp` | `LeetCode.exe` |
| `LeetCodeTests` | Unit tests using Google Test | `LeetCodeTests.exe` / `leetcode_tests` |

Solutions are header-only `.hpp` files. They are compiled because `LeetCode.cpp` includes all of them. The test project includes individual solution headers as needed.

## Building on Windows (Visual Studio)

Open `src/solution.slnx` in Visual Studio. Both projects are configured for x64.

### How Google Test Works in Visual Studio

- The `LeetCodeTests` project builds an executable that runs all tests.
- Visual Studio's **Test Explorer** (Test → Test Explorer) auto-discovers gtest tests and shows them in a tree view. You can run or debug individual tests from there.
- The test project references solution headers via include path (`../LeetCode`).
- Gtest headers and libraries come from vcpkg (triplet: `x64-win-utc`).
- `tests_main.cpp` provides the `main()` function that initializes and runs Google Test.

## Building on Linux

### Prerequisites

- GCC 12+ or Clang 15+ (for C++20 support)
- CMake 3.20+
- Git (for FetchContent to download Google Test)

### Using build.sh

From the repo root:

```bash
chmod +x build.sh
./build.sh            # Debug build (default)
./build.sh Release    # Release build
```

The script will:
1. Create a `build/` directory
2. Configure CMake with Google Test (fetched automatically via `FetchContent`)
3. Build both the main binary and test binary
4. Run all tests via `ctest`

Output binaries:
- `build/leetcode` — main executable (compiles all solutions)
- `build/leetcode_tests` — test runner

### Manual CMake commands

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
cmake --build . --parallel $(nproc)
ctest --output-on-failure
```

To build without tests:

```bash
cmake .. -DBUILD_TESTS=OFF
cmake --build .
```

### Running specific tests

After building, you can run the test binary directly with gtest filters:

```bash
# Run all tests
./build/leetcode_tests

# Run tests matching a pattern
./build/leetcode_tests --gtest_filter="TwoSum.*"
./build/leetcode_tests --gtest_filter="GroupAnagrams.*"

# List all available tests
./build/leetcode_tests --gtest_list_tests
```

## Using CLion

CLion is CMake-native. Just open the repo root folder and it picks up `CMakeLists.txt` automatically. No extra configuration needed.

CLion will:
- Configure the project and fetch Google Test via `FetchContent`
- Show `leetcode` and `leetcode_tests` as run targets in the toolbar
- Auto-discover all gtest tests in the built-in test runner (pass/fail UI, re-run individual tests, debugging)
- Provide code navigation and refactoring across solution headers and test files

CLion ignores the `.vcxproj` / `.slnx` files — those are Visual Studio-only. The CMake build covers everything with the same source files, include paths, and test framework.

## Adding a New Test File

1. Create `src/LeetCodeTests/NNNNN_ProblemNameTests.cpp`:

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

2. For Visual Studio: add the file to `LeetCodeTests.vcxproj` under the `<ItemGroup>` containing `<ClCompile>` entries:

```xml
<ClCompile Include="NNNNN_ProblemNameTests.cpp" />
```

3. For CMake/CLion: no changes needed — the glob `src/LeetCodeTests/*Tests.cpp` picks it up automatically.

## Adding a New Solution

1. Create `src/LeetCode/NNNNN_ProblemName.hpp` with `#pragma once` at the top.
2. Name the class `SolutionNNNNN` (use the problem number as suffix).
3. If the solution uses `TreeNode` or `ListNode`, add `#include "common_types.hpp"`.
4. Add `#include "NNNNN_ProblemName.hpp"` to `src/LeetCode/LeetCode.cpp`.
5. For Visual Studio: add a `<ClInclude>` entry to `LeetCode.vcxproj` and `LeetCode.vcxproj.filters`.
6. For CMake/CLion: no changes needed.

## CI Notes

- No vcpkg is needed on Linux. Google Test is downloaded at configure time via CMake `FetchContent`.
- The same `src/LeetCodeTests/*Tests.cpp` files are compiled on both Windows (Visual Studio + vcpkg) and Linux (CMake + FetchContent).
- All solution headers and test files are portable C++20 with no platform-specific code.
