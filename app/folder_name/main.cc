#include "board.h"

static void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm__("nop");
        //Take one clock cycle, execute nothing
        //"nop" = no operation
    }
}

int main()
{
    board_led_init();
    while (1)
    {
        board_led_toggle();
        delay(1000000);
    }
}