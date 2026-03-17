#include "board.h"
#include "gpio.h"

#define BOARD_LED_PORT GPIOA
#define BOARD_LED_PIN 5U

#define BOARD_BTN_PORT GPIOC
#define BOARD_BTN_PIN 13U

void Board_Init()
{
    gpio_pin_config_t cfg;

    GPIO_ClockEnable(BOARD_LED_PORT);

    cfg.pin = BOARD_LED_PIN;
    cfg.mode = ST_GPIO_MODE_OUTPUT;
    cfg.otype = ST_GPIO_OTYPE_PP;
    cfg.speed = ST_GPIO_SPEED_LOW;
    cfg.pupd = ST_GPIO_PUPD_NONE;

    GPIO_Init(BOARD_LED_PORT, &cfg);
    GPIO_WritePin(BOARD_LED_PORT, BOARD_LED_PIN, ST_GPIO_PIN_SET);  // Turn LED on
}

void Board_LED_Toggle(void)
{
    GPIO_TogglePin(BOARD_LED_PORT, BOARD_LED_PIN);
}

uint8_t Board_Button_IsPressed(void)
{
    // Placeholder implementation
    return 0;
}
