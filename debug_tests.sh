#!/bin/bash

echo "=== CMake Test Debug Script ==="

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Error: build directory not found"
    echo "Run: cmake -B build && cmake --build build"
    exit 1
fi

cd build

echo "1. Checking test executables..."
find . -name "*_tests" -type f -executable

echo "2. Checking CTest configuration..."
ctest -N

echo "3. Running tests with verbose output..."
ctest -VV --output-on-failure

echo "4. Running tests directly..."
for test_exe in $(find . -name "*_tests" -type f -executable); do
    echo "=== Running $test_exe ==="
    $test_exe --gtest_list_tests
    $test_exe --gtest_output=xml:$(basename $test_exe).xml
done

echo "=== Debug complete ==="