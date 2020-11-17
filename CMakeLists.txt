cmake_minimum_required(VERSION 3.16)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(Matrix main.cpp)
target_link_libraries(Matrix gtest gtest_main)