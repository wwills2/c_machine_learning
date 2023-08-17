cmake_minimum_required(VERSION 3.20)
project(c_machine_learning C)

set(CMAKE_C_STANDARD 90)

add_library(c_machine_learning STATIC c_source/lib_ml_basics.c
        c_source/log.h
        c_source/log.c)
