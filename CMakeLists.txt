cmake_minimum_required(VERSION 3.0)


project(LINK)

# set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")


set(CMAKE_BUILD_TYPE Debug)
# set( CMAKE_BUILD_TYPE "Release")

include_directories(${CMAKE_SOURCE_DIR}/include)


set(SRC 
    src/setexAPI.c 
    )

add_executable(main.exe main.c ${SRC})