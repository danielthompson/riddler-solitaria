cmake_minimum_required(VERSION 3.6)
project(solitaria)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(solitaria ${SOURCE_FILES})

project(solitaria-mt)
set(SOURCE_FILES multithreaded.cpp)
add_executable(solitaria-mt ${SOURCE_FILES})