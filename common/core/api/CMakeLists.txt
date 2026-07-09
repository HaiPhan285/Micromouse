# api module
add_library(api STATIC)

target_include_directories(api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(api PUBLIC
    core
)
