#include "board.h"

int main() {
  if (!MM::board_init()) {
    return 1;
  }

  MM::Board& board{MM::get_board()};
  board.counter.start();

  for (;;) {
    __asm volatile("wfi");
  }
}
