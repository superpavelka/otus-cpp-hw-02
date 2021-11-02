cmake_minimum_required(VERSION 3.2)

project(ALLOCATOR VERSION 0.0.1)

add_library(a_lib STATIC Placeholder.cpp MyAllocator.h)

set_target_properties(
    a_lib PROPERTIES
    CXX_VERSION 11
    CXX_VERSION_REQUIRED ON
    LINKER_LANGUAGE CXX
)

target_include_directories(
    a_lib
    PRIVATE
    {CMAKE_CURRENT_BINARY_DIR}
)