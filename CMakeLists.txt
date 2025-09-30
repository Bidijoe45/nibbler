cmake_minimum_required(VERSION 3.16)
project(nibbler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 6)

# LIBRARIES

# Install graphics libraries (SDL, raylib, sfml)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/tty-gui)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/sdl)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/raylib)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/sfml)

# Cmd line parser
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/cmdparser)

add_subdirectory(src)
add_subdirectory(test)