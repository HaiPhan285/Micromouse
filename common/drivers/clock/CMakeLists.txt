# clock driver module
add_library(clock STATIC)

target_include_directories(clock PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
