
#include "board.h"
#include "delay.h"
#include "nav.h"

using namespace MM;

int main() {
  if (!bsp_init()) {
    return 1;
  }

  Board& hw = get_board();
  Navigation nav;

  while (hw.start_bt.read() != 0) {
  }
  Utils::delay_ms(50); // debounce
  while (hw.start_bt.read() != 0) {
  }

  while (1) {
    const IrValues& ir = hw.ir_controller.get_ir_vals();
    nav.update(ir);
    nav.execute(hw.motion_controller, ir);
  }

  return 0;
}
