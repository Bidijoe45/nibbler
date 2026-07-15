cmake_minimum_required(VERSION 3.22)
project(nibbler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 6)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# LIBRARIES

# Install graphics libraries (SDL, raylib, sfml)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/tty-gui)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/sdl)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/raylib)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/sfml)

# Cmd line parser
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/cmdparser)

#JSON parser
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/json)

add_subdirectory(src)
add_subdirectory(test)