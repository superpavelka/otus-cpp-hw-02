cmake_minimum_required(VERSION 3.9)

project(MAIN VERSION 0.0.1)

add_executable(main main.cpp)

set_target_properties(
    main PROPERTIES
    CXX_VERSION 17
    CXX_VERSION_REQUIREMENTS ON
)

target_include_directories(
    main
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
    main
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../allocator_lib
)

target_include_directories(
    main
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../mylist_lib
)

target_link_libraries(main mylist_lib a_lib)


