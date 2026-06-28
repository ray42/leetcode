cmake_minimum_required(VERSION 3.20)
project(LeetCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Solutions are header-only (.hpp files)
set(SOLUTION_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/LeetCode")

# Main executable
add_executable(leetcode
    src/LeetCode/LeetCode.cpp
)
target_include_directories(leetcode PRIVATE ${SOLUTION_INCLUDE_DIR})

# Tests using Google Test
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()

    # Fetch GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    # Prevent GoogleTest from overriding compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Gather all test files (same location as Visual Studio project)
    file(GLOB TEST_SOURCES "src/LeetCodeTests/*Tests.cpp")

    add_executable(leetcode_tests
        ${TEST_SOURCES}
    )

    target_include_directories(leetcode_tests PRIVATE
        ${SOLUTION_INCLUDE_DIR}
    )

    target_link_libraries(leetcode_tests PRIVATE
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(leetcode_tests)
endif()
