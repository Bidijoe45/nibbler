cmake_minimum_required(VERSION 3.16)

project(ClippCmdParser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    ${PROJECT_NAME}
    GIT_REPOSITORY https://github.com/muellan/clipp
    GIT_TAG v1.1.0
)
FetchContent_MakeAvailable(${PROJECT_NAME})

FetchContent_GetProperties(
  ${PROJECT_NAME}
  SOURCE_DIR CMD_PARSER_SOURCE_DIR
  BINARY_DIR CMD_PARSER_BINARY_DIR
  POPULATED CMD_PARSER_POPULATED
)

message(cmd_SOURCE_DIR=${PROJECT_NAME}_SOURCE_DIR)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMD_PARSER_SOURCE_DIR}/include)