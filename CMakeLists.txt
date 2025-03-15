cmake_minimum_required(VERSION 3.15) # Or a more recent version

project(xost VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic") # Optional, but recommended

# Create a library
add_library(xost
    src/xost/core.cpp # Example source file
    src/xost/utility.cpp # Another example
    # ... add other source files here
)

# Include directories
target_include_directories(xost
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include> #For install target
    PRIVATE
        src
)

# Example: If you have external dependencies (e.g., a header-only library), you can add them like this:
# find_package(fmt REQUIRED) # Example using fmt
# target_link_libraries(xost PRIVATE fmt::fmt)

# Installation
install(TARGETS xost
    EXPORT xost-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include
)

# Create a CMake export file (optional, but recommended)
install(EXPORT xost-targets
    FILE xost-config.cmake
    NAMESPACE xost::
    DESTINATION lib/cmake/xost
)

# Generate a xost-config.cmake file to be used by downstream projects
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "xost-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/xost-config-version.cmake"
    DESTINATION lib/cmake/xost
)

# Example for adding tests (if you have them)
# enable_testing()
# add_executable(xost_tests tests/main.cpp tests/test_core.cpp)
# target_link_libraries(xost_tests xost)
# add_test(NAME xost_core_tests COMMAND xost_tests)

# Example for adding documentation (if you have doxygen for example)
# find_package(Doxygen)
# if(DOXYGEN_FOUND)
#     add_custom_target(doc
#         COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
#         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#         COMMENT "Generating API documentation with Doxygen"
#         VERBATIM
#     )
# endif()