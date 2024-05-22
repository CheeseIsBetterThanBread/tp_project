cmake_minimum_required(VERSION 3.10)
project(Command)

set(COMMAND Command.cpp AddShipCommand.cpp FireAtCommand.cpp)
add_library(command SHARED ${COMMAND})

target_include_directories(command PRIVATE ${CMAKE_SOURCE_DIR}/include/connection/command)