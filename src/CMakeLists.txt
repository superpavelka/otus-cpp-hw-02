cmake_minimum_required(VERSION 3.2)

project(MAIN VERSION 0.0.1)

add_executable(main main.cpp)

set_target_properties(
    main PROPERTIES
    CXX_VERSION 11
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

target_link_libraries(main a_lib)

if (MSVC)
    target_compile_options(main PRIVATE
        /W4
    )
    target_compile_options(a_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(main PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(a_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
