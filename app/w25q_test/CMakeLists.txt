add_f411_firmware(w25q_test
    BSP spi_app_bsp
    BSP_DIRECTORY ${CMAKE_SOURCE_DIR}/app/spi_test/bsp_f411
    INCLUDES
        ${CMAKE_SOURCE_DIR}/app/spi_test
        ${CMAKE_SOURCE_DIR}/app/spi_test/bsp_f411
        ${CMAKE_SOURCE_DIR}/common/core/periph/w25q128
    LIBRARIES core w25q128
)
