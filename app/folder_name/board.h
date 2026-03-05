#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include "gpio.h"

/*=========================================================
  Board: NUCLEO-F446RE
  - LED (LD2)  : PA5
  - Button (B1): PC13 (ACTIVE LOW)
=========================================================*/

/* --- LED --- */
#define BOARD_LED_PORT GPIOA
#define BOARD_LED_PIN 5U

/* --- Button --- */
#define BOARD_BTN_PORT GPIOC
#define BOARD_BTN_PIN 13U

/*=========================================================
  Init helpers
=========================================================*/
static inline void Board_LED_Init(void)
{
    GPIO_PinConfig_t cfg = {0};

    GPIO_ClockEnable(BOARD_LED_PORT);

    cfg.pin = BOARD_LED_PIN;
    cfg.mode = GPIO_MODE_OUTPUT;
    cfg.otype = GPIO_OTYPE_PP;
    cfg.speed = GPIO_SPEED_LOW;
    cfg.pupd = GPIO_PUPD_NONE;
    cfg.af = GPIO_AF0; /* not used for output, but fill anyway */

    GPIO_Init(BOARD_LED_PORT, &cfg);
}

static inline void Board_Button_Init(void)
{
    GPIO_PinConfig_t cfg = {0};

    GPIO_ClockEnable(BOARD_BTN_PORT);

    cfg.pin = BOARD_BTN_PIN;
    cfg.mode = GPIO_MODE_INPUT;
    cfg.otype = GPIO_OTYPE_PP;  /* not used for input */
    cfg.speed = GPIO_SPEED_LOW; /* not used for input */
    cfg.pupd =
        GPIO_PUPD_NONE; /* Nucleo button uses external resistor network */
    cfg.af = GPIO_AF0;

    GPIO_Init(BOARD_BTN_PORT, &cfg);
}

/*=========================================================
  LED control
=========================================================*/
static inline void Board_LED_On(void)
{
    GPIO_WritePin(BOARD_LED_PORT, BOARD_LED_PIN, GPIO_PIN_SET);
}

static inline void Board_LED_Off(void)
{
    GPIO_WritePin(BOARD_LED_PORT, BOARD_LED_PIN, GPIO_PIN_RESET);
}

static inline void Board_LED_Toggle(void)
{
    GPIO_TogglePin(BOARD_LED_PORT, BOARD_LED_PIN);
}

/*=========================================================
  Button read
  NOTE: PC13 is active-low on Nucleo boards:
        pressed  -> 0
        released -> 1
=========================================================*/
static inline uint8_t Board_Button_IsPressed(void)
{
    return (GPIO_ReadPin(BOARD_BTN_PORT, BOARD_BTN_PIN) == GPIO_PIN_RESET) ? 1U
                                                                           : 0U;
}

#endif /* BOARD_H */