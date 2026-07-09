# utils module
add_library(utils STATIC)

target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(utils PUBLIC
    core
)
