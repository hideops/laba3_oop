cmake_minimum_required(VERSION 3.10)
project(FiguresProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(figures_main main.cpp)
add_executable(figures_tests tests.cpp)

target_link_libraries(figures_tests GTest::gtest GTest::gtest_main)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(figures_main PRIVATE -Wall -Wextra)
    target_compile_options(figures_tests PRIVATE -Wall -Wextra)
endif()
