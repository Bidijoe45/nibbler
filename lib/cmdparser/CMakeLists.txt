cmake_minimum_required(VERSION 3.16)

project(ClippCmdParser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Fetching ClippCmdParser(muellan/clipp) ...")
include(FetchContent)
FetchContent_Declare(
    ${PROJECT_NAME}
    GIT_REPOSITORY https://github.com/muellan/clipp
    GIT_TAG v1.1.0
)
FetchContent_MakeAvailable(${PROJECT_NAME})
message(STATUS "DONE Fetching ClippCmdParser(muellan/clipp)")

FetchContent_GetProperties(
  ${PROJECT_NAME}
  SOURCE_DIR ClippCmdParser_SOURCE_DIR
  BINARY_DIR ClippCmdParser_BINARY_DIR
  POPULATED ClippCmdParser_POPULATED
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${ClippCmdParser_SOURCE_DIR}/include)