cmake_minimum_required(VERSION 3.10)
project(Sea_battle)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++20")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -fsanitize=undefined")
set(CMAKE_EXECUTABLE_SUFFIX ".out")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(include)
add_executable(exe main.cpp)

add_subdirectory(src)
add_subdirectory(tests)
target_link_libraries(exe command
                          connection
                          internal)