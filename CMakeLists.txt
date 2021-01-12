cmake_minimum_required(VERSION 3.16)

add_subdirectory(tests)

project(Matrix)

add_executable(${PROJECT_NAME}  main.cpp Matrix_random.cpp Buf.h)

