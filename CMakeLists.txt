cmake_minimum_required(VERSION 3.25)
project(railway-multigraphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Core library (shared between main executable and tests)
add_library(railway_multigraphs_lib
    src/unvisited_queue.cpp
    src/network.cpp
)

# Linking to railway_multigraphs_lib requires headers in src
target_include_directories(railway_multigraphs_lib PUBLIC src)

# Build the main executable
add_executable(railway-multigraphs src/main.cpp)
target_link_libraries(railway-multigraphs PRIVATE railway_multigraphs_lib)

# Build tests
find_package(GTest REQUIRED)
add_executable(railway-multigraphs-tests
    tests/test_network.cpp
    tests/test_stop.cpp
    tests/test_track.cpp
    tests/test_unvisited_queue.cpp
)
target_link_libraries(railway-multigraphs-tests PRIVATE railway_multigraphs_lib GTest::gtest_main)

# Integrate with CTest
include(CTest)
include(GoogleTest)
gtest_discover_tests(railway-multigraphs-tests EXTRA_ARGS --gtest_color=yes)
