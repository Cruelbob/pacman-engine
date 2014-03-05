cmake_minimum_required(VERSION 2.8)

project(pacman-engine)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -pedantic -Wall -Werror -Wfatal-errors")

if(${EMSCRIPTEN})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-warn-absolute-paths")

    SET(CMAKE_LINK_LIBRARY_SUFFIX "")
    SET(CMAKE_STATIC_LIBRARY_PREFIX "")
    SET(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
    SET(CMAKE_SHARED_LIBRARY_PREFIX "")
    SET(CMAKE_SHARED_LIBRARY_SUFFIX ".bc")
    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".bc")

    set(EMSCRIPTEN 1)
elseif(UNIX)
    set(UNIX 1)
endif()

add_subdirectory(lib)
add_subdirectory(tests)
