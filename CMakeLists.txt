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
    src/main.cpp
)

# Add Google Test submodule
add_subdirectory(external/googletest)

# Add the test executable
add_executable(main_tests
    src/Network.cpp
    src/Station.cpp
    tests/main_tests.cpp
)

# Discover and enable tests
include(GoogleTest)
gtest_discover_tests(main_tests)

# Enable testing for this project
enable_testing()

# Link Google Test libraries
target_link_libraries(main_tests PRIVATE gtest gtest_main)

# Register the test executable with CTest
add_test(NAME MainTests COMMAND main_tests --gtest_color=yes)