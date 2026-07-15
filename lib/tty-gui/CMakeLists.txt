cmake_minimum_required(VERSION 3.22)

project(TTY_GUI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS
    src/tty_gui.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
