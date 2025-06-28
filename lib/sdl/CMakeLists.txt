cmake_minimum_required(VERSION 3.16)

project(SDL_Wrapper)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS
    src/sdl_wrapper.cpp
)

include(FetchContent)
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.16
)
FetchContent_MakeAvailable(SDL)

# Create your game executable target as usual
add_library(SDL_Wrapper SHARED ${SRCS})
target_link_libraries(SDL_Wrapper PRIVATE SDL3::SDL3)
target_include_directories(SDL_Wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)