cmake_minimum_required(VERSION 3.17)
project(SocketServer C)

set(CMAKE_C_STANDARD 99)

add_executable(Server server.c)
add_executable(Client client.c)