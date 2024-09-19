cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(Project CXX)
include_directories(include)

add_executable(cache_test test/list_test.cpp)
target_link_libraries(cache_test gtest_main gtest)