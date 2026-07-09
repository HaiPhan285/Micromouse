# algorithm module
add_library(algorithm STATIC)

target_include_directories(algorithm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(algorithm PUBLIC
    core
)
