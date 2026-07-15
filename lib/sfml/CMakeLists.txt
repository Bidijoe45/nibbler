cmake_minimum_required(VERSION 3.22)

project(SFML_GUI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS ON)
set(SFML_BUILD_AUDIO OFF)

set(SRCS
    src/sfml_gui.cpp
)

message(STATUS "Fetching SFML_GUI(SFML/SFML) ...")
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 3.0.2
)
message(STATUS "Fetching SFML_GUI(SFML/SFML) ...")

FetchContent_MakeAvailable(SFML)
add_library(${PROJECT_NAME} SHARED ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
