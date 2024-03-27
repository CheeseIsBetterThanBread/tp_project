cmake_minimum_required(VERSION 3.10)
project(Connection)

set(CONNECTION Interactor.cpp ObserverSystem.cpp RemoteServer.cpp)
add_library(connection STATIC ${CONNECTION})

target_include_directories(connection PRIVATE ${CMAKE_SOURCE_DIR}/include/connection)