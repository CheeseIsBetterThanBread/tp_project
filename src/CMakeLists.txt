cmake_minimum_required(VERSION 3.10)
project(Internal)

set(SOURCES Adapter.cpp Battlefield.cpp)
add_subdirectory(connection)
add_subdirectory(command)
add_library(internal STATIC ${SOURCES})