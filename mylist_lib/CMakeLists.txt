cmake_minimum_required(VERSION 3.9)

project(MYLIST VERSION 0.0.1)

add_library(mylist_lib STATIC Placeholder.cpp MyList.h)

set_target_properties(
    mylist_lib PROPERTIES
    CXX_VERSION 17
    CXX_VERSION_REQUIRED ON
    LINKER_LANGUAGE CXX
)

target_include_directories(
    mylist_lib
    PRIVATE
    {CMAKE_CURRENT_BINARY_DIR}
)