#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

void Board_Init(void);
void Board_LED_Toggle(void);
uint8_t Board_Button_IsPressed(void);

#endif