
#include "board.h"
#include "w25q.h"
#include <array>

using namespace MM;

int main(void) {
  BSP_Init();

  Board spi_board = Get_Board();

  W25q flash{spi_board.spi1, spi_board.cs};

  [[maybe_unused]] bool status = flash.reset();

  std::array<uint8_t, 1> status_reg_val;
  status = flash.status_reg_read(W25q::StatusRead::STATUS_REGISTER_3, status_reg_val);
  status = flash.init();
  status = flash.status_reg_read(W25q::StatusRead::STATUS_REGISTER_3, status_reg_val);

  status = flash.status_reg_write(W25q::StatusWrite::STATUS_REGISTER_1, (1 << 2), (1 << 2));
  status = flash.status_reg_read(W25q::StatusRead::STATUS_REGISTER_1, status_reg_val);
  status = flash.status_reg_write(W25q::StatusWrite::STATUS_REGISTER_1, (1 << 2), (0 << 2));
  status = flash.status_reg_read(W25q::StatusRead::STATUS_REGISTER_1, status_reg_val);

  std::array<uint8_t, 3> txbuf{0x02u, 0x04u, 0x06u};
  std::array<uint8_t, 3> rxbuf{};
  status = flash.page_program(1, 1, 1, 0, txbuf, rxbuf);

  status = flash.block_erase(1);
  status = flash.read(1, 1, 1, 0, rxbuf);

  std::array<uint8_t, 1> txbuf2{0x08u};
  std::array<uint8_t, 1> rxbuf2{};
  status = flash.page_program(0, 1, 0, 0, txbuf2, rxbuf2);
  status = flash.sector_erase(0, 1);
  status = flash.read(0, 1, 0, 0, rxbuf2);

  status = flash.page_program(0, 1, 0, 0, txbuf2, rxbuf2);
  status = flash.chip_erase();
  status = flash.read(0, 1, 0, 0, rxbuf2);

  status = flash.block_lock(1);
  status = flash.block_unlock(1);

  while (1) {
  }

  return 0;
} // namespace MM