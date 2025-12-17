cmake_minimum_required(VERSION 3.29)
project(MultithreadedArithmetic)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(
        "/Users/mac_aleksandr/googletest"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest_build"
)

add_executable(MultithreadedArithmetic main.cpp
        LoggerAndFileTask.h
)

target_link_libraries(MultithreadedArithmetic PUBLIC GTest::gtest_main)

add_executable(Tests test.cpp
)

target_link_libraries(Tests PRIVATE GTest::gtest_main)
