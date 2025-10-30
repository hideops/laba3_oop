cmake_minimum_required(VERSION 3.12)
project(geometry)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(main_app main.cpp)
add_executable(test_app tests.cpp)

target_link_libraries(test_app GTest::gtest GTest::gtest_main)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main_app PRIVATE -Wall -Wextra)
    target_compile_options(test_app PRIVATE -Wall -Wextra)
endif()
