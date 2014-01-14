cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCE_EXE *.cpp
                             *.h)

include_directories(${PACMAN_INCLUDE_DIRS})

add_executable(run_and_exit ${SOURCE_EXE})

target_link_libraries(run_and_exit ${PACMAN_LIBS})