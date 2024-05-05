cmake_minimum_required(VERSION 3.10)
project(Sea_battle)

list(APPEND CMAKE_CXX_FLAGS "-O2 -std=c++20")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -fsanitize=address -fsanitize=undefined")
set(CMAKE_EXECUTABLE_SUFFIX ".out")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(exe main.cpp)

target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(exe command
                          connection
                          internal
                          interface)