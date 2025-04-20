cmake_minimum_required(VERSION 3.10)

add_subdirectory(concurr)
add_subdirectory(mailbox)

add_library(xost STATIC
    blank.cpp
)
target_link_libraries(xost PRIVATE concurr mailbox)

# Optionally, install the library and header files
install(TARGETS xost ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/concurr/ ${CMAKE_CURRENT_SOURCE_DIR}/mailbox/ DESTINATION include FILES_MATCHING PATTERN "*.h")