#ifndef ST_GPIO_H
#define ST_GPIO_H

#include <stdint.h>
#include "stm32f4xx.h"

/*=====================================================
GPIO ENUMS
=====================================================*/

typedef enum
{
    ST_GPIO_MODE_INPUT  = 0,
    ST_GPIO_MODE_OUTPUT = 1,
    ST_GPIO_MODE_AF     = 2,
    ST_GPIO_MODE_ANALOG = 3
} ST_GPIO_Mode_t;

typedef enum
{
    ST_GPIO_OTYPE_PP = 0,
    ST_GPIO_OTYPE_OD = 1
} ST_GPIO_OType_t;

typedef enum
{
    ST_GPIO_SPEED_LOW    = 0,
    ST_GPIO_SPEED_MEDIUM = 1,
    ST_GPIO_SPEED_FAST   = 2,
    ST_GPIO_SPEED_HIGH   = 3
} ST_GPIO_Speed_t;

typedef enum
{
    ST_GPIO_PUPD_NONE = 0,
    ST_GPIO_PUPD_PU   = 1,
    ST_GPIO_PUPD_PD   = 2
} ST_GPIO_PuPd_t;

typedef enum
{
    ST_GPIO_PIN_RESET = 0,
    ST_GPIO_PIN_SET   = 1
} ST_GPIO_PinState_t;

/*=====================================================
CONFIG STRUCT
=====================================================*/

typedef struct
{
    uint8_t pin;
    ST_GPIO_Mode_t mode;
    ST_GPIO_OType_t otype;
    ST_GPIO_Speed_t speed;
    ST_GPIO_PuPd_t pupd;
    uint8_t af;
} ST_GPIO_PinConfig_t;

/*=====================================================
API
=====================================================*/

void GPIO_ClockEnable(GPIO_TypeDef *port);
void GPIO_Init(GPIO_TypeDef *port, ST_GPIO_PinConfig_t *config);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, ST_GPIO_PinState_t state);
ST_GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);
void GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin);

#endif // ST_GPIO_H
