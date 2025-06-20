cmake_minimum_required(VERSION 3.16)
set(NIBBLER_TEST_EXEC nibbler_tests)
set(SRCS
    test.cpp
)

add_executable(${NIBBLER_TEST_EXEC} ${SRCS})
target_include_directories(${NIBBLER_TEST_EXEC} PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${NIBBLER_TEST_EXEC} PRIVATE nibbler_main_lib)