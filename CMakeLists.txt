cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(Project CXX)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    /usr/local/boost_1_87_0
)

set(SRC_LIST 
    # ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/global_random.cpp
)


add_executable(list_test test/list_test.cpp ${SRC_LIST})
add_executable(cm_sketch_test test/cm_sketch_test.cpp ${SRC_LIST})
add_executable(cache_test test/cache_test.cpp ${SRC_LIST})
target_link_libraries(list_test gtest_main gtest)
target_link_libraries(cm_sketch_test gtest_main gtest)
target_link_libraries(cache_test gtest_main gtest)