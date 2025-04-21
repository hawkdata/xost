
cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${CMAKE_SOURCE_DIR}/xost)
add_subdirectory(metricshm)

add_executable(demo demo.cpp)

target_link_libraries(demo PRIVATE xost)
target_include_directories(demo PRIVATE ${CMAKE_SOURCE_DIR}/xost)