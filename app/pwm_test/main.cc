#include "board.h"

namespace {
constexpr int kDutyCycleSequence[]{25, 90, 42};

void holdDutyCycle() {
  for (unsigned int cycle{0}; cycle < 4'000'000; ++cycle) {
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
    for (const int duty_cycle : kDutyCycleSequence) {
      board.pwm.set_duty_cycle(duty_cycle);
      holdDutyCycle();
    }
  }
}
