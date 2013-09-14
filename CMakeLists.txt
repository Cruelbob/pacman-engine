cmake_minimum_required(VERSION 2.8)

project(pacman-engine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "release")
endif()

add_subdirectory(lib)
add_subdirectory(examples)
