cmake_minimum_required(VERSION 3.24)
project(XServer)

set(CMAKE_CXX_STANDARD 20)

include_directories(third_party/asio/include)
include_directories(include)


#echo Server
add_executable(echo_server src/echoServer/main.cpp
        src/echoServer/echo_server.cpp)


#echo Client
add_executable(echo_client
        src/echoClient/main.cpp)
