add_executable(floodfill_test floodfill_test.cc)
target_link_libraries(floodfill_test PRIVATE algorithm)

add_test(NAME floodfill COMMAND floodfill_test)

add_executable(simulation_protocol_test
    simulation_protocol_test.cc
    ${CMAKE_SOURCE_DIR}/app/mms_sim/sim/mms.cc
)
target_include_directories(simulation_protocol_test PRIVATE
    ${CMAKE_SOURCE_DIR}/app/mms_sim/sim
)

add_test(NAME simulation_protocol COMMAND simulation_protocol_test)
