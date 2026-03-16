add_library(hal STATIC
    st_gpio.cpp
)

target_include_directories(hal PUBLIC
    .
    ..
    ${CMAKE_SOURCE_DIR}/mcu_support/CMSIS/include
    ${CMAKE_SOURCE_DIR}/common/drivers/time
    ${CMAKE_SOURCE_DIR}
    )

if(MCU_FAMILY STREQUAL "STM32F4")
    target_include_directories(hal PUBLIC ${CMAKE_SOURCE_DIR}/mcu_support/stm32/f4xx)
    target_link_libraries(hal PUBLIC st_f4_support)
elseif(MCU_FAMILY STREQUAL "STM32F7")
    target_include_directories(hal PUBLIC ${CMAKE_SOURCE_DIR}/mcu_support/stm32/f7xx)
    target_link_libraries(hal PUBLIC st_f7_support)
elseif(MCU_FAMILY STREQUAL "STM32L4")
    target_include_directories(hal PUBLIC ${CMAKE_SOURCE_DIR}/mcu_support/stm32/l4xx)
    target_link_libraries(hal PUBLIC st_l4_support)
elseif(MCU_FAMILY STREQUAL "STM32H5")
    target_include_directories(hal PUBLIC ${CMAKE_SOURCE_DIR}/mcu_support/stm32/h5xx)
    target_link_libraries(hal PUBLIC st_h5_support)
endif()

target_link_libraries(hal PUBLIC
    core 
)