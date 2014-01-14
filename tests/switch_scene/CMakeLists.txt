cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCE_EXE *.cpp
                             *.h)

include_directories(${PACMAN_INCLUDE_DIRS})

add_executable(switch_scene ${SOURCE_EXE})

target_link_libraries(switch_scene ${PACMAN_LIBS})