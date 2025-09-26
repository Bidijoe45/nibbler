cmake_minimum_required(VERSION 3.16)

project(GLFW_GUI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS
    src/glfw_gui.cpp
)

include(FetchContent)
FetchContent_Declare(
    GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(GLFW)

add_library(${PROJECT_NAME} SHARED ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
