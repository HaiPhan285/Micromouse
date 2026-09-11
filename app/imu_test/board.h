
#pragma once
#include "bno055_imu.h"
#include "delay.h"
#include "gpio.h"
#include "i2c.h"

namespace MM {

struct Board {
  Bno055& imu;
};

bool bsp_init(void);
Board& get_board(void);

} // namespace MM