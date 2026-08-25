add_f411_firmware(pid_controller
    COPY_ELF
    BSP pid_bsp
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/bsp_f411
    LIBRARIES motion
)
