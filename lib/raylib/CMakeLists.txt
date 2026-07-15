cmake_minimum_required(VERSION 3.22)

project(RAYLIB_GUI)

set(BUILD_EXAMPLES OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS ON)

set(SRCS
    src/raylib_gui.cpp
)

message(STATUS "Fetching RAYLIB_GUI(raysan5/raylib) ...")
include(FetchContent)
FetchContent_Declare(
    RAYLIB
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(RAYLIB)
message(STATUS "DONE Fetching RAYLIB_GUI(raysan5/raylib) ...")

add_library(${PROJECT_NAME} SHARED ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
