cmake_minimum_required(VERSION 3.14)
project(TheHarmoninator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Collect all .cpp files in the src/ directory
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(executeInput ${SOURCES})

find_package(PkgConfig)
pkg_check_modules(SERIAL libserial)

target_include_directories(executeInput PRIVATE ${SERIAL_INCLUDE_DIRS})
target_link_libraries(executeInput PRIVATE ${SERIAL_LDFLAGS} ${CMAKE_THREAD_LIBS_INIT})
