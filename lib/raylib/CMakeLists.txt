cmake_minimum_required(VERSION 3.16)

project(RAYLIB_GUI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS "ON")

set(SRCS
    src/raylib_gui.cpp
)

include(FetchContent)
FetchContent_Declare(
    RAYLIB
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(RAYLIB)

add_library(${PROJECT_NAME} SHARED ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
