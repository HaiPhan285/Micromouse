#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include "gpio.h"

/**
 * Board: STM32L476RG
 * LED (LD2): PA5
 */

//LED Config
#define BOARD_LED_PORT (GPIOA)
#define BOARD_LED_PIN (5U)

void board_led_init()
{
    GPIO_PinConfig_t cfg = {0};
    cfg.pin = BOARD_LED_PIN;
    cfg.mode = GPIO_Mode_t::OUTPUT;
    cfg.otype = GPIO_OType_t::PP;
    cfg.speed = GPIO_Speed_t::LOW;
    cfg.pupd = GPIO_PuPd_t::NOPULL;

    GPIO_Init(BOARD_LED_PORT, BOARD_LED_PIN, &cfg);
}

void board_led_toggle()
{
    GPIO_TogglePin(BOARD_LED_PORT, BOARD_LED_PIN);
}
#endif  // BOARD_H