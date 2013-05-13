cmake_minimum_required(VERSION 2.8)

project(pacman_engine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
    message(SEND_ERROR "Failed to find SDL")
    return()
else()
    include_directories(${SDL_INCLUDE_DIR})
endif()

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(SEND_ERROR "Failed to find GLEW")
    return()
else()
    include_directories(${GLEW_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(SEND_ERROR "Failed to find OpenGL")
    return()
else()
    include_directories(${OpenGL_INCLUDE_DIR})
endif()

add_definitions(-DNO_SDL_GLEXT)

set(SOURCE_LIB pacman/game.cpp
               pacman/game_state.cpp
               pacman/sdl/sdl_graphics_context.cpp
               pacman/opengl/opengl_context.cpp
               pacman/opengl/opengl_image.cpp)

set(SOURCE_EXE game_state_example/game_state_example.cpp
               game_state_example/sample_game_state.cpp)

include_directories(pacman)
include_directories(pacman/mathgl)
include_directories(game_state_example)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_library(pacman_engine STATIC ${SOURCE_LIB})

add_executable(example ${SOURCE_EXE})

target_link_libraries(example pacman_engine
                              ${SDL_LIBRARY}
                              ${GLEW_LIBRARY}
                              ${OPENGL_LIBRARY})
