#pragma once

#include "pwm.h"

namespace MM {

struct Board {
  Pwm& pwm;
};

bool bsp_init();
Board& get_board();

} // namespace MM
