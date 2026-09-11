add_library(i2c_bsp STATIC
    f411_board.cc
)

target_include_directories(i2c_bsp PUBLIC
  .
  ../
)

target_link_libraries(i2c_bsp PUBLIC
    driver
)
