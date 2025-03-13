include(FetchContent)

FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(music_test ${TEST_SOURCES})

enable_testing()

add_test(NAME music_test COMMAND music_test)

target_link_libraries(music_test PUBLIC music_lib gtest)

include(GoogleTest)
gtest_discover_tests(music_test)
