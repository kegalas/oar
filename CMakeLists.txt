cmake_minimum_required(VERSION 3.17)

set(SRC_LIST main.cpp geometry.cpp)

project(oar VERSION 0.1.0)

add_executable(learn ${SRC_LIST})
