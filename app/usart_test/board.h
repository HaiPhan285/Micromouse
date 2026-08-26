#pragma once

#include <cstdint>

#include "gpio.h"
#include "usart.h"

extern uint8_t rx_byte;
namespace MM {
struct Board {
  Usart& usart;
  Gpio& rx;
  Gpio& tx;
};

bool bsp_init();
Board& get_board();

} // namespace MM
