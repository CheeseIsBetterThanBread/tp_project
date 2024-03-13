cmake_minimum_required(VERSION 3.10)
project(Commands)

set(SOURCES AddShipCommand.cpp Command.cpp FireAtCommand.cpp Adapter.cpp)
add_subdirectory(connection)
add_library(commands STATIC ${SOURCES})