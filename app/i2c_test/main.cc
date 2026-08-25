#include "board.h"

namespace {
constexpr uint8_t kBmp390Address{0x76};
constexpr uint8_t kChipIdRegister{0x00};

void waitForNextRead() {
  for (unsigned int cycle{0}; cycle < 100'000; ++cycle) {
    __asm volatile("nop");
  }
}
} // namespace

int main() {
  if (!MM::bsp_init()) {
    return 1;
  }

  MM::Board& board{MM::get_board()};
  uint8_t chip_id{0};
  for (;;) {
    board.i2c.mem_read(&chip_id, 1, kChipIdRegister, kBmp390Address);
    waitForNextRead();
  }
}
