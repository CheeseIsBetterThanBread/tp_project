cmake_minimum_required(VERSION 3.10)
project(Connection)

add_subdirectory(command)
set(CONNECTION Interactor.cpp ObserverSystem.cpp RemoteServer.cpp)
add_library(connection SHARED ${CONNECTION})

target_include_directories(connection PRIVATE ${CMAKE_SOURCE_DIR}/include/connection
                                              ${CMAKE_SOURCE_DIR}/include/connection/command)
target_link_libraries(connection command)