cmake_minimum_required(VERSION 3.14)
project(Harmoninator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
