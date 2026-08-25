#pragma once

#include "encoder.h"
#include "gpio.h"

namespace MM {

struct Board {
  Encoder& encoder;
  Gpio& enc_ch1;
  Gpio& enc_ch2;
};

bool bsp_init();
Board& get_board();
} // namespace MM
