cmake_minimum_required(VERSION 3.15)
project(HW2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW2
        voter.c
        voter.h)
