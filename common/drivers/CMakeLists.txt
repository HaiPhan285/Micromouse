if(TARGET_DEVICE MATCHES "STM32")
    add_subdirectory(platform/stm32)
endif()

add_library(driver INTERFACE)

target_include_directories(driver INTERFACE
    IO 
)

if(TARGET hal)
    target_link_libraries(driver INTERFACE
        hal
    )
endif()