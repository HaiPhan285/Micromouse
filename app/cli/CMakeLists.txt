add_f411_firmware(cli
    BSP cli_bsp
    INCLUDES
        ${CMAKE_SOURCE_DIR}/common/core/cli
        ${CMAKE_SOURCE_DIR}/common/core/navigation
        ${CMAKE_SOURCE_DIR}/common/core/api
        ${CMAKE_SOURCE_DIR}/common/core/algorithm
        ${CMAKE_SOURCE_DIR}/common/core/periph/irsensor
        ${CMAKE_SOURCE_DIR}/common/drivers/io
    LIBRARIES cli_core navigation
)
