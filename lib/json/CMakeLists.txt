cmake_minimum_required(VERSION 3.22)

project(JSONParser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Fetching JSONParser(nlohmann/json) ...")
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)
message(STATUS "DONE Fetching JSONParser(nlohmann/json) ...")

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE nlohmann_json::nlohmann_json)