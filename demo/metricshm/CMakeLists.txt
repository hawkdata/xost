
cmake_minimum_required(VERSION 3.10)


add_executable(mproducer metricproducer.cpp)
target_link_libraries(mproducer PRIVATE xost)

add_executable(mreader metricreader.cpp)
target_link_libraries(mreader PRIVATE xost)