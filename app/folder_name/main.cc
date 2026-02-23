#include "board.h"

static void delay(volatile uint32_t count)
{
    while (count--) {
        __asm__("nop");
    }
}

int main(void)
{
    Board_LED_Init();

    while (1)
    {
        Board_LED_Toggle();
        delay(500000);
    }
}