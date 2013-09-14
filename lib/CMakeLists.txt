cmake_minimum_required(VERSION 2.8)

find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
    message(SEND_ERROR "Failed to find SDL")
    return()
endif()

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(SEND_ERROR "Failed to find GLEW")
    return()
endif()

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(SEND_ERROR "Failed to find OpenGL")
    return()
endif()

add_definitions(-DNO_SDL_GLEXT)

file(GLOB_RECURSE SOURCE_LIB *.cpp
                             *.hpp
                             *.h)

set(PACMAN_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
                        ${SDL_INCLUDE_DIR}
                        ${GLEW_INCLUDE_DIR}
                        ${OpenGL_INCLUDE_DIR}
)

include_directories(${PACMAN_INCLUDE_DIRS})

add_library(pacman STATIC ${SOURCE_LIB})

set(PACMAN_INCLUDE_DIRS ${PACMAN_INCLUDE_DIRS} PARENT_SCOPE)
set(PACMAN_LIBS pacman
                ${SDL_LIBRARY}
                ${GLEW_LIBRARY}
                ${OPENGL_LIBRARY}
    PARENT_SCOPE
)
