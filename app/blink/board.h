#pragma once
#include "gpio.h"

namespace MM {

struct Board {
  Gpio& led;
};

bool board_init();
Board& get_board();

} // namespace MM
