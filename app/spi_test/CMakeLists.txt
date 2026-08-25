add_f411_firmware(spi_test
    BSP spi_app_bsp
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/bsp_f411
    LIBRARIES core w25q128
)
