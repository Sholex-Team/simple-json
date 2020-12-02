cmake_minimum_required(VERSION 3.17)
project(simple-json VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)

add_executable(simple_json main.cpp)

target_link_libraries(simple_json PRIVATE types)