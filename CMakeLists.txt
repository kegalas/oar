cmake_minimum_required(VERSION 3.17)
project(OAR VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${PROJECT_SOURCE_DIR}/src/include")
include_directories(BEFORE src)

add_subdirectory(src)


