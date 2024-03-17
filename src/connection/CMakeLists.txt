cmake_minimum_required(VERSION 3.10)
project(Connection)

set(CONNECTION Interactor.cpp ObserverSystem.cpp RemoteServer.cpp)
add_library(connection STATIC ${CONNECTION})