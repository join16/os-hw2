cmake_minimum_required(VERSION 3.3)
project(hw2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES ./*.c lib/*.c lib/*.h)

set(SOURCE_FILES ${SOURCES})
add_executable(hw2 ${SOURCE_FILES})