cmake_minimum_required(VERSION 3.15)
project(socket C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c)
add_executable(tcpserver tcpserver.c)
add_executable(tcpclient tcpclient.c)