# periph module
add_library(periph STATIC)

target_include_directories(periph PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(periph PUBLIC
    core
)
