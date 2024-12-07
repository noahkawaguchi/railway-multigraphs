cmake_minimum_required(VERSION 3.16)
project(RailwaySimulator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the 'include' directory for public headers
include_directories(include)

# Add the main executable
add_executable(railway_simulator 
    src/Network.cpp
    src/Station.cpp
    src/UnvisitedQueue.cpp
    src/main.cpp
)

# Add Google Test submodule
add_subdirectory(external/googletest)

# Add the test executable
add_executable(tests
    src/Station.cpp
    tests/test_Station.cpp
    src/Network.cpp
    tests/test_Network.cpp
    src/UnvisitedQueue.cpp
    tests/test_UnvisitedQueue.cpp
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