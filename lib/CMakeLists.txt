cmake_minimum_required(VERSION 2.8)

#if(UNIX)
#    find_package(OpenGL REQUIRED)
#    if(NOT OPENGL_FOUND)
#        message(SEND_ERROR "Failed to find OpenGL")
#        return()
#    endif()
#endif()

if(${EMSCRIPTEN}) #check before linux because emscripten mimics linux enviroment
    add_definitions(-DSDL=1)
    add_definitions(-DGLES2=1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(OpenGL REQUIRED)
    if(NOT OPENGL_FOUND)
        message(SEND_ERROR "Failed to find OpenGL")
        return()
    endif()

    set(PACMAN_LIBS
        ${PACMAN_LIBS}
        rt
        SDL2
        ${OPENGL_LIBRARY})

    add_definitions(-DSDL2=1)
    add_definitions(-DGL=1)
endif()

file(GLOB SOURCE_LIB
    src/*.cpp
#    src/*.h
    include/*.h
    include/pacman/*.h
)

set(PACMAN_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenGL_INCLUDE_DIR}
)


if(${EMSCRIPTEN}) #check before linux because emscripten mimics linux enviroment
    file(GLOB_RECURSE SOURCE_LIB_EMSCRIPTEN
        src/platform/emscripten/*.cpp
        src/platform/sdl/*.cpp
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
        src/platform/sdl2/*.cpp
        include/platform/linux/pacman/*.h
    )
    set(SOURCE_LIB ${SOURCE_LIB} ${SOURCE_LIB_LINUX})
    set(PACMAN_INCLUDE_DIRS
        ${PACMAN_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/linux
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
