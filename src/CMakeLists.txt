cmake_minimum_required(VERSION 3.10)
project(Internal)

add_subdirectory(connection)
add_subdirectory(interface)

set(SOURCES Battlefield.cpp)
add_library(internal SHARED ${SOURCES})

target_include_directories(internal PRIVATE ${CMAKE_SOURCE_DIR}/include)