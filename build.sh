#!/bin/bash
set -e

BUILD_DIR="build"
BUILD_TYPE="${1:-Debug}"

echo "=== LeetCode Linux Build ==="
echo "Build type: ${BUILD_TYPE}"

# Create build directory
mkdir -p "${BUILD_DIR}"

# Configure
cmake -S . -B "${BUILD_DIR}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DBUILD_TESTS=ON

# Build
cmake --build "${BUILD_DIR}" --parallel "$(nproc)"

echo ""
echo "=== Build complete ==="
echo "Binary:  ${BUILD_DIR}/leetcode"
echo "Tests:   ${BUILD_DIR}/leetcode_tests"

# Run tests
echo ""
echo "=== Running tests ==="
cd "${BUILD_DIR}"
ctest --output-on-failure
