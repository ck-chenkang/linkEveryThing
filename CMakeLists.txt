cmake_minimum_required(VERSION 3.0)

project(LINK)

# set(DebugENV TRUE)
set(DebugENV FALSE)

if(${DebugENV})
    # set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

    set(CMAKE_BUILD_TYPE Debug)
    # set( CMAKE_BUILD_TYPE "Release")

    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/inc)
    include_directories(${CMAKE_SOURCE_DIR})

    # link_directories(/home/ck/curl-ubuntu-64/lib)
    # link_directories(/home/ck/curl-arm-32/lib)

    set(SRC 
        # src/setexAPI.c
        # src/config.c
        # src/http.c
        )
    add_executable(main.exe main.c ${SRC})
    # target_link_libraries(main.exe libcurl.so)
    target_link_libraries(main.exe libdl.so)
else()
    set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

    set(CMAKE_BUILD_TYPE Debug)
    # set( CMAKE_BUILD_TYPE "Release")

    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/inc)
    include_directories(${CMAKE_SOURCE_DIR})

    # link_directories(/home/ck/curl-ubuntu-64/lib)
    # link_directories(/home/ck/curl-arm-32/lib)

    set(SRC 
        # src/setexAPI.c
        # src/config.c
        # src/http.c
        )
    add_executable(main.exe main.c ${SRC})
    # target_link_libraries(main.exe libcurl.so)
    target_link_libraries(main.exe libdl.so)
endif()

