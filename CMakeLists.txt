cmake_minimum_required(VERSION 3.20)
project(valgrind_mem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(valgrind_mem
        utils.cpp
        utils.h
        valgrind_analysis.cpp
        valgrind_analysis.h file.cpp file.h list.cpp list.h)
