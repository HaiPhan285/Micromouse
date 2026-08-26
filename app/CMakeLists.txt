set(embedded_applications
    adc_test
    blink
    cli
    drv8231_test
    encoder_test
    hc-05_test
    i2c_test
    imu_test
    ir_single_test
    ir_test
    ir_threshold_test
    motor_test
    nav_app
    pcb_blinky
    pid_controller
    pwm_test
    spi_test
    timebase_test
    trap_test
    usart_test
    w25q_test
)

if(TARGET_DEVICE STREQUAL "STM32F411")
    foreach(application IN LISTS embedded_applications)
        add_subdirectory(${application})
    endforeach()
elseif(TARGET_DEVICE STREQUAL "NATIVE")
    add_subdirectory(mms_sim)
endif()
