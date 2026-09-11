
#include "board.h"
#include <array>

using namespace MM;

int main(void) {
  BSP_Init();

  Board& spi_board = Get_Board();

  std::array<uint8_t, 4> tx_buffer = {0x90, 0x00, 0x00, 0x00};

  std::array<uint8_t, 2> rx_buffer;

  while (1) {
    spi_board.cs.cs_enable();
    spi_board.spi1.seq_transfer(tx_buffer, rx_buffer);
    spi_board.cs.cs_disable();
  }

  return 0;
}
