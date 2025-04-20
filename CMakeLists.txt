cmake_minimum_required(VERSION 3.15) # Or a more recent version

project(xost VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic") # Optional, but recommended


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(xost)
add_subdirectory(demo)