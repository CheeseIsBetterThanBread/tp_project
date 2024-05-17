cmake_minimum_required(VERSION 3.10)
project(Interface)

set(INTERFACE Adapter.cpp Bot.cpp CommandLine.cpp)
add_library(interface SHARED ${INTERFACE})

target_include_directories(interface PRIVATE ${CMAKE_SOURCE_DIR}/include/interface)