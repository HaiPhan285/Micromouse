# cli module
add_library(cli STATIC)

target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cli PUBLIC
    core
)
