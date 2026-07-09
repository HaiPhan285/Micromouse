# navigation module
add_library(navigation STATIC)

target_include_directories(navigation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(navigation PUBLIC
    core
)
