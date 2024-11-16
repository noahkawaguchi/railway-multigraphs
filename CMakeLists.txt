cmake_minimum_required(VERSION 3.16)
project(RailwaySimulator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(railway_simulator
    src/main.cpp
    src/Station.cpp
    src/Track.cpp
    src/Network.cpp
)

# Add include directories
target_include_directories(railway_simulator PRIVATE include)