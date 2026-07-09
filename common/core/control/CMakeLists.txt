# control module
add_library(control STATIC)

target_include_directories(control PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(control PUBLIC
    core
)
