set(EXECUTABLE folder_name)
set(LDF ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE}.ld)

set(PREPROCESS_DEFS
    -DDEF_FLASH_START_ADDR=0x8000000
    -DDEF_FLASH_SIZE=1024K
)

add_subdirectory_for(STM32 bsp)

add_executable_for(STM32 ${EXECUTABLE} ${LDF}
    main.cc
    ${STARTUP_FILE}
)

target_include_directories_for(STM32 ${EXECUTABLE} #test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries_for(STM32 ${EXECUTABLE} PRIVATE
    ${EXECUTABLE}_bsp
)

target_preprocess_for(STM32 ${EXECUTABLE} ${LINKER_SCRIPT} ${LDF} ${PREPROCESS_DEFS})
