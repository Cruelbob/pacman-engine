cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(${EMSCRIPTEN}) #check before linux because emscripten mimics linux enviroment
    set(SDL 1)
    set(GLES2 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(SDL2 REQUIRED)
    if(NOT SDL2_FOUND)
        message(SEND_ERROR "Failed to find OpenGL")
        return()
    endif()

    find_package(OpenGL REQUIRED)
    if(NOT OPENGL_FOUND)
        message(SEND_ERROR "Failed to find OpenGL")
        return()
    endif()

    find_package(PNG REQUIRED)
    if(NOT PNG_FOUND)
        message(SEND_ERROR "Failed to find PNG library")
        return()
    endif()

    set(PACMAN_LIBS
        ${PACMAN_LIBS}
        rt
        ${SDL2_LIBRARY}
        ${OPENGL_gl_LIBRARY}
        ${PNG_LIBRARIES}
    )

    set(SDL 2)
    set(GL 1)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/include/pacman/Config.h")

file(GLOB SOURCE_LIB
    src/*.cpp
    include/*.h
    include/pacman/*.h
)

file(GLOB_RECURSE EIGEN_SOURCE
    include/Eigen/*
)

set(SOURCE_LIB ${SOURCE_LIB} ${EIGEN_SOURCE})

set(PACMAN_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


if(${EMSCRIPTEN}) #check before linux because emscripten mimics linux enviroment
    file(GLOB_RECURSE SOURCE_LIB_EMSCRIPTEN
        src/platform/emscripten/*.cpp
        src/platform/sdl/*.cpp
        src/platform/opengl/*.cpp
        include/platform/emscripten/pacman/*.h
    )
    set(SOURCE_LIB ${SOURCE_LIB} ${SOURCE_LIB_EMSCRIPTEN})
    set(PACMAN_INCLUDE_DIRS
        ${PACMAN_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/emscripten
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file(GLOB_RECURSE SOURCE_LIB_LINUX
        src/platform/linux/*.cpp
        src/platform/sdl/*.cpp
        src/platform/opengl/*.cpp
        include/platform/linux/pacman/*.h
    )
    set(SOURCE_LIB ${SOURCE_LIB} ${SOURCE_LIB_LINUX})
    set(PACMAN_INCLUDE_DIRS
        ${PACMAN_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/linux
        ${SDL2_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${PNG_INCLUDE_DIRS}
    )
endif()

include_directories(${PACMAN_INCLUDE_DIRS})

add_library(pacman STATIC ${SOURCE_LIB})

set(PACMAN_INCLUDE_DIRS ${PACMAN_INCLUDE_DIRS} PARENT_SCOPE)
set(PACMAN_LIBS
    ${PACMAN_LIBS}
    pacman
    PARENT_SCOPE
)
