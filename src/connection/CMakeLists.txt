cmake_minimum_required(VERSION 3.10)
project(Connection)

set(CONNECTION Battlefield.cpp Interactor.cpp ObserverSystem.cpp RemoteServer.cpp)
add_library(connection STATIC ${CONNECTION})