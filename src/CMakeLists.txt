
set(NIBBLER_MAIN_LIB nibbler_main_lib)
set(SRCS
    nibbler.cpp
)

add_library(${NIBBLER_MAIN_LIB} ${SRCS})
target_include_directories(${NIBBLER_MAIN_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${NIBBLER_MAIN_LIB})