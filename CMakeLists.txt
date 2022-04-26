cmake_minimum_required(VERSION 3.16)
project(ProcessSync C)

set(CMAKE_C_STANDARD 99)

add_executable(ProcessSync server.c stack.c client.c)
