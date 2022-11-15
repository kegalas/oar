cmake_minimum_required(VERSION 3.17)

set(SRC_LIST main.cpp tga_image.cpp geometry.cpp raster.cpp)

project(oar VERSION 0.1.0)

add_executable(oar ${SRC_LIST})
