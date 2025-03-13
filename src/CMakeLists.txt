# Collect all .cpp files in the src/ directory and its subdirectories
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

# Define the executable
add_executable(music_run ${SOURCES})

find_package(PkgConfig)
pkg_check_modules(SERIAL libserial)

target_include_directories(music_run PRIVATE ${SERIAL_INCLUDE_DIRS})
target_link_libraries(music_run PRIVATE ${SERIAL_LDFLAGS} ${CMAKE_THREAD_LIBS_INIT})

add_library(music_lib STATIC ${SOURCES})
target_include_directories(music_lib PRIVATE ${SERIAL_INCLUDE_DIRS})
target_link_libraries(music_lib PRIVATE ${SERIAL_LDFLAGS} ${CMAKE_THREAD_LIBS_INIT})