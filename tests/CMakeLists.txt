cmake_minimum_required(VERSION 3.14)
project(TheHarmoninatorTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

# Collect all .cpp files in the unit/ directory and its subdirectories
file(GLOB_RECURSE TEST_SOURCES "../*.cpp")

# include_directories(../src)
# file(GLOB_RECURSE SOURCES "../src/*.cpp")
# add_library(my_lib SOURCES)

# Define the test executable
add_executable(runTests ${TEST_SOURCES})

target_link_libraries(runTests gtest gmock gtest_main)
target_link_libraries(runTests my_lib)

# Enable testing
enable_testing()

# Add test with CTest
add_test(NAME HarmonicaTest COMMAND runTests)
