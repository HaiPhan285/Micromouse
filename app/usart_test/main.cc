#include <array>

#include "board.h"

uint8_t rx_byte;

namespace {
const std::array<uint8_t, 20> kMessage{"XuperMouse!\r\n"};

void waitForTransmitPeriod() {
  for (unsigned int cycle{0}; cycle < 1'000'000; ++cycle) {
    __asm volatile("nop");
  }
}
} // namespace

int main() {
  if (!MM::bsp_init()) {
    return 1;
  }

  MM::Board& board{MM::get_board()};
  for (;;) {
    board.usart.send(kMessage);
    waitForTransmitPeriod();
  }
}
