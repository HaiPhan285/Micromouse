# math module
add_library(math STATIC)

target_include_directories(math PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(math PUBLIC
    core
)
