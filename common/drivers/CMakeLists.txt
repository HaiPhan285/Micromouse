add_subdirectory(platform/stm32)

add_library(driver INTERFACE)

target_include_directories(driver INTERFACE
    IO 
)

target_link_libraries(driver INTERFACE
    hal
    
)