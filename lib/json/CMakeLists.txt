cmake_minimum_required(VERSION 3.16)

project(JSONParser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Fetching JSONParser(nlohmann/json) ...")
include(FetchContent)
FetchContent_Declare(
    ${PROJECT_NAME}
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(${PROJECT_NAME})
message(STATUS "DONE Fetching JSONParser(nlohmann/json) ...")

FetchContent_GetProperties(
  ${PROJECT_NAME}
  SOURCE_DIR JSONParser_SOURCE_DIR
  BINARY_DIR JSONParser_BINARY_DIR
  POPULATED JSONParser_POPULATED
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${JSONParser_SOURCE_DIR}/include)