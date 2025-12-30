cmake_minimum_required(VERSION 3.16)
project(railway-multigraphs)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the "include" directory for public headers
include_directories(include)

# Add the main executable
add_executable(railway-multigraphs
    src/Network.cpp
    src/UnvisitedQueue.cpp
    src/main.cpp
)

# Add Google Test submodule
add_subdirectory(external/googletest)

# Add the test executable
add_executable(tests
    src/Network.cpp
    tests/test_Network.cpp
    src/UnvisitedQueue.cpp
    tests/test_UnvisitedQueue.cpp
    tests/test_Stop.cpp
    tests/test_Track.cpp
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
