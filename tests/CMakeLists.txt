project(MatrixGtest)

set(CMAKE_CXX_STANDARD 20)

#[[add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)]]

add_definitions(-DGTESTS)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}  ../main.cpp ../tests.cpp ../Matrix_random.cpp)

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main  Threads::Threads)


#target_link_libraries(Matrix gtest gtest_main)