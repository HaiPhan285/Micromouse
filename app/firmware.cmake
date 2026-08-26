include_guard(GLOBAL)

function(add_f411_firmware name)
    set(options COPY_ELF)
    set(one_value_args BSP BSP_DIRECTORY)
    set(multi_value_args INCLUDES LIBRARIES)
    cmake_parse_arguments(FIRMWARE
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        ${ARGN}
    )

    if(NOT TARGET_DEVICE STREQUAL "STM32F411")
        return()
    endif()

    if(NOT FIRMWARE_BSP)
        message(FATAL_ERROR "${name} must declare a BSP target")
    endif()

    if(NOT FIRMWARE_BSP_DIRECTORY)
        set(FIRMWARE_BSP_DIRECTORY bsp_f411)
    endif()

    if(NOT TARGET ${FIRMWARE_BSP})
        add_subdirectory(
            "${FIRMWARE_BSP_DIRECTORY}"
            "${CMAKE_CURRENT_BINARY_DIR}/${FIRMWARE_BSP}"
        )
    endif()

    set(linker_file "${CMAKE_CURRENT_BINARY_DIR}/${name}.ld")
    set(linker_definitions
        -DDEF_FLASH_START_ADDR=0x8000000
        -DDEF_FLASH_SIZE=1024K
    )

    add_executable_for(${TARGET_DEVICE} ${name} ${linker_file}
        main.cc
        ${STARTUP_FILE}
    )

    target_include_directories(${name} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        ${FIRMWARE_INCLUDES}
    )
    target_link_libraries(${name} PRIVATE
        ${FIRMWARE_BSP}
        ${FIRMWARE_LIBRARIES}
    )
    target_preprocess_for(
        ${TARGET_DEVICE}
        ${name}
        ${LINKER_SCRIPT}
        ${linker_file}
        ${linker_definitions}
    )

    if(FIRMWARE_COPY_ELF)
        add_custom_command(TARGET ${name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${name}>
                "${CMAKE_CURRENT_BINARY_DIR}/${name}.elf"
            VERBATIM
        )
    endif()
endfunction()

function(add_f411_board target)
    set(multi_value_args SOURCES PUBLIC_INCLUDES PRIVATE_INCLUDES LIBRARIES)
    cmake_parse_arguments(BOARD "" "" "${multi_value_args}" ${ARGN})

    if(NOT BOARD_SOURCES)
        message(FATAL_ERROR "${target} must declare at least one source file")
    endif()

    add_library(${target} STATIC ${BOARD_SOURCES})
    target_include_directories(${target}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/..
            ${BOARD_PUBLIC_INCLUDES}
        PRIVATE
            ${BOARD_PRIVATE_INCLUDES}
    )
    target_link_libraries(${target} PUBLIC ${BOARD_LIBRARIES})
endfunction()
