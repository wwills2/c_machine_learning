cmake_minimum_required(VERSION 3.20)
project(c_machine_learning C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -pedantic")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(C_SOURCES_DIR c_source)
set(TESTING_DIR test)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/cmake-build-debug)

add_library(lib_ml_basics STATIC
        ${C_SOURCES_DIR}/lib_ml_basics.h
        ${C_SOURCES_DIR}/lib_ml_basics.c
        ${C_SOURCES_DIR}/log.h
        ${C_SOURCES_DIR}/log.c)

add_executable(c_smoke_test ${TESTING_DIR}/smoke_test.c)
target_link_libraries(c_smoke_test ${CMAKE_BINARY_DIR}/lib_ml_basics.a)
add_test(test_lib_ml_basics c_smoke_test)
