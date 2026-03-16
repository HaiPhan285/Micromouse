#include "st_gpio.h"

/*=====================================================
CLOCK ENABLE
=====================================================*/

void GPIO_ClockEnable(GPIO_TypeDef* port)
{
    if (port == GPIOA)
        __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC)
        __HAL_RCC_GPIOC_CLK_ENABLE();
#ifdef GPIOD
    else if (port == GPIOD)
        __HAL_RCC_GPIOD_CLK_ENABLE();
#endif
#ifdef GPIOE
    else if (port == GPIOE)
        __HAL_RCC_GPIOE_CLK_ENABLE();
#endif
#ifdef GPIOF
    else if (port == GPIOF)
        __HAL_RCC_GPIOF_CLK_ENABLE();
#endif
#ifdef GPIOG
    else if (port == GPIOG)
        __HAL_RCC_GPIOG_CLK_ENABLE();
#endif
#ifdef GPIOH
    else if (port == GPIOH)
        __HAL_RCC_GPIOH_CLK_ENABLE();
#endif
}

/*=====================================================
INIT
=====================================================*/

void GPIO_Init(GPIO_TypeDef* port, ST_GPIO_PinConfig_t* cfg)
{
    uint32_t pin = cfg->pin;

    port->MODER &= ~(0x3 << (pin * 2));
    port->MODER |= (cfg->mode << (pin * 2));

    port->OTYPER &= ~(1 << pin);
    port->OTYPER |= (cfg->otype << pin);

    port->OSPEEDR &= ~(0x3 << (pin * 2));
    port->OSPEEDR |= (cfg->speed << (pin * 2));

    port->PUPDR &= ~(0x3 << (pin * 2));
    port->PUPDR |= (cfg->pupd << (pin * 2));
}

/*=====================================================
WRITE
=====================================================*/

void GPIO_WritePin(GPIO_TypeDef* port, uint8_t pin, ST_GPIO_PinState_t state)
{
    if (state == ST_GPIO_PIN_SET)
        port->BSRR = (1U << pin);
    else
        port->BSRR = (1U << (pin + 16));
}

/*=====================================================
READ
=====================================================*/

ST_GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef* port, uint8_t pin)
{
    return (port->IDR & (1U << pin)) ? ST_GPIO_PIN_SET : ST_GPIO_PIN_RESET;
}

/*=====================================================
TOGGLE
=====================================================*/

void GPIO_TogglePin(GPIO_TypeDef* port, uint8_t pin)
{
    port->ODR ^= (1U << pin);
}
