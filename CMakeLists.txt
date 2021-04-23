cmake_minimum_required(VERSION 3.0)

project(LINK)

set(RELEASEENV False) # True False

if(${RELEASEENV})
    # set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
    # set( CMAKE_BUILD_TYPE "Release")
    # link_directories(/home/ck/curl-ubuntu-64/lib)
    # link_directories(/home/ck/curl-arm-32/lib)
    # target_link_libraries(main.exe libcurl.so)    
    set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")
set(CMAKE_BUILD_TYPE Debug)

set(SRC 
    src/connectConfig.c
    src/cJSON.c
    src/setexdata.c
    src/setexAPI.c
)

add_executable(main.exe main.c ${SRC})
target_link_libraries(main.exe libdl.so pthread)
