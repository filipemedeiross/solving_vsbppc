cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(my_lib src/instance.cpp src/bin.cpp)

target_include_directories(my_lib PUBLIC src)

enable_testing()
add_subdirectory(tests)