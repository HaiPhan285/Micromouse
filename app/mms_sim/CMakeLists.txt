if(NOT TARGET_DEVICE STREQUAL "NATIVE")
    return()
endif()

add_executable(mms_sim
    main.cc
    sim/mms.cc
)

target_include_directories(mms_sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/sim
)
target_link_libraries(mms_sim PRIVATE algorithm)
