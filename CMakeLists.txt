cmake_minimum_required(VERSION 3.0)


project(LINK)
# set cmopiler is arm 
# set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE Debug)


add_executable(main.exe main.cpp)