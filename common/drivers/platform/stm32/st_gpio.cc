#include "st_gpio.h"

/*=====================================================
CLOCK ENABLE
=====================================================*/

void GPIO_ClockEnable(GPIO_TypeDef* port)
{
    if (port == GPIOA)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (port == GPIOB)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (port == GPIOC)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
#ifdef GPIOD
    else if (port == GPIOD)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
#endif
#ifdef GPIOE
    else if (port == GPIOE)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
#endif
#ifdef GPIOF
    else if (port == GPIOF)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
#endif
#ifdef GPIOG
    else if (port == GPIOG)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
#endif
#ifdef GPIOH
    else if (port == GPIOH)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
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
