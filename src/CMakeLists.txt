cmake_minimum_required(VERSION 3.16)
set(NIBBLER_MAIN_LIB nibbler_main_lib)
set(SRCS
    config.cpp
    dynamic_lib.cpp
    nibbler.cpp
    snake_game.cpp
    snake.cpp
    fruit.cpp
)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")

add_library(${NIBBLER_MAIN_LIB} ${SRCS})
target_link_libraries(${NIBBLER_MAIN_LIB} PRIVATE JSONParser)
target_include_directories(${NIBBLER_MAIN_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    ClippCmdParser
    ${NIBBLER_MAIN_LIB}
)
