add_f411_firmware(trap_test
    BSP trap_bsp
    INCLUDES
        ${CMAKE_SOURCE_DIR}/common/core/api
        ${CMAKE_SOURCE_DIR}/common/core/periph/irsensor
        ${CMAKE_SOURCE_DIR}/common/drivers/io
        ${CMAKE_SOURCE_DIR}/common/drivers/time
    LIBRARIES api
)
