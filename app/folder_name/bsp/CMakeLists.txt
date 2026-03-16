add_library_for(STM32 ${EXECUTABLE}_bsp hardware_specific.cc)
target_include_directories_for(STM32 ${EXECUTABLE}_bsp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries_for(STM32 ${EXECUTABLE}_bsp
    driver
    hal
)
