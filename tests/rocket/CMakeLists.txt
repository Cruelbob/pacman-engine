cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCE_EXE *.cpp
                             *.h)

include_directories(${PACMAN_INCLUDE_DIRS})

add_executable(rocket ${SOURCE_EXE})

target_link_libraries(rocket ${PACMAN_LIBS})

add_custom_command(TARGET rocket POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/rocket.png ${CMAKE_CURRENT_BINARY_DIR}/rocket.png
)
