cmake_minimum_required(VERSION 3.16)
project(railway-multigraphs)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the main executable
add_executable(railway-multigraphs
    src/network.cpp
    src/unvisited_queue.cpp
    src/main.cpp
)

# Add Google Test submodule
add_subdirectory(external/googletest)

# Add the test executable
add_executable(tests
    src/network.cpp
    tests/test_network.cpp
    src/unvisited_queue.cpp
    tests/test_unvisited_queue.cpp
    tests/test_stop.cpp
    tests/test_track.cpp
)

# Discover and enable tests
include(GoogleTest)
gtest_discover_tests(tests)

# Enable testing for this project
enable_testing()

# Link Google Test libraries
target_link_libraries(tests PRIVATE gtest gtest_main)

# Register the test executable with CTest
add_test(NAME Tests COMMAND tests --gtest_color=yes)
