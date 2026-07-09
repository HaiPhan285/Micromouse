# memory driver module
add_library(memory STATIC)

target_include_directories(memory PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
