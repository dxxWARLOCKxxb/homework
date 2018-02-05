cmake_minimum_required(VERSION 3.9)
project(The_Matrix)

set(CMAKE_CXX_STANDARD 11)

add_executable(The_Matrix main.cpp matrix.cpp matrix.h)
find_package(Threads)
target_link_libraries(The_Matrix ${CMAKE_THREAD_LIBS_INIT})