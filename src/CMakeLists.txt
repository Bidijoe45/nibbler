cmake_minimum_required(VERSION 3.16)
set(NIBBLER_MAIN_LIB nibbler_main_lib)
set(SRCS
    config.cpp
    dynamic_lib.cpp
    nibbler.cpp
    snake.cpp
)

set(CMAKE_CXX_FLAGS, "g")

configure_file("../nibbler-config.json" "nibbler-config.json")

add_library(${NIBBLER_MAIN_LIB} ${SRCS})
target_include_directories(${NIBBLER_MAIN_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${NIBBLER_MAIN_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ClippCmdParser)

# Link main program
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${NIBBLER_MAIN_LIB})


# Just for testing, THIS SHOULD NOT BE USED
# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${NIBBLER_MAIN_LIB} SDL_Wrapper)