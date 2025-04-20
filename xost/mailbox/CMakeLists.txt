cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
add_library(mailbox STATIC
        ${SOURCES}
)

target_include_directories(mailbox PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)