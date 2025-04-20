cmake_minimum_required(VERSION 3.10)

# Use file(GLOB) to find all C++ source files in the current directory and subdirectories.
file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(concurr STATIC
        ${SOURCES}
)

target_include_directories(concurr PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
