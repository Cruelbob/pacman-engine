cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCE_EXE *.cpp
                             *.h)

include_directories(${PACMAN_INCLUDE_DIRS})

add_executable(game_state_example ${SOURCE_EXE})

target_link_libraries(game_state_example ${PACMAN_LIBS})

add_custom_command(TARGET game_state_example POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/loading_image.bmp ${CMAKE_CURRENT_BINARY_DIR}/loading_image.bmp
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/loading_text.bmp ${CMAKE_CURRENT_BINARY_DIR}/loading_text.bmp
)
