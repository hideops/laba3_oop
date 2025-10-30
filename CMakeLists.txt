cmake_minimum_required(VERSION 3.10)
project(geom)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(app main.cpp)
add_executable(tests tests.cpp)

target_link_libraries(tests GTest::gtest GTest::gtest_main)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(app PRIVATE -Wall)
    target_compile_options(tests PRIVATE -Wall)
endif()
