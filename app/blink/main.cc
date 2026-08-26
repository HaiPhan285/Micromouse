#include "board.h"

namespace {
constexpr unsigned int kToggleDelayCycles{100'000};

void waitBetweenToggles() {
  for (unsigned int cycle{0}; cycle < kToggleDelayCycles; ++cycle) {
    __asm volatile("nop");
  }
}
} // namespace

int main() {
  if (!MM::board_init()) {
    return 1;
  }

  MM::Board& board{MM::get_board()};
  for (;;) {
    board.led.toggle();
    waitBetweenToggles();
  }
}
