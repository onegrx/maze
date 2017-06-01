cmake_minimum_required(VERSION 3.6)
project(maze)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)


set(SOURCE_FILES
        crystals/crystals.cpp)

add_executable(maze ${SOURCE_FILES})