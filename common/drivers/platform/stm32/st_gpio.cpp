#include "st_gpio.hpp"

namespace st::gpio
{

/*==============================
CLOCK ENABLE
==============================*/

void GPIO::enableClock(GPIO_TypeDef* port)
{
    if (port == GPIOA)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (port == GPIOB)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (port == GPIOC)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (port == GPIOD)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if (port == GPIOE)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
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

/*==============================
INIT
==============================*/

void GPIO::init(GPIO_TypeDef* port, const PinConfig& cfg)
{
    uint32_t pin = cfg.pin;

    /* MODE */
    port->MODER &= ~(0x3U << (pin * 2));
    port->MODER |= (static_cast<uint32_t>(cfg.mode) << (pin * 2));

    /* OUTPUT TYPE */
    port->OTYPER &= ~(1U << pin);
    port->OTYPER |= (static_cast<uint32_t>(cfg.otype) << pin);

    /* SPEED */
    port->OSPEEDR &= ~(0x3U << (pin * 2));
    port->OSPEEDR |= (static_cast<uint32_t>(cfg.speed) << (pin * 2));

    /* PULL-UP / PULL-DOWN */
    port->PUPDR &= ~(0x3U << (pin * 2));
    port->PUPDR |= (static_cast<uint32_t>(cfg.pull) << (pin * 2));

    /* ALTERNATE FUNCTION */
    if (cfg.mode == Mode::Alternate)
    {
        if (pin < 8)
        {
            port->AFR[0] &= ~(0xFU << (pin * 4));
            port->AFR[0] |= (cfg.alternate << (pin * 4));
        }
        else
        {
            uint32_t pos = pin - 8;
            port->AFR[1] &= ~(0xFU << (pos * 4));
            port->AFR[1] |= (cfg.alternate << (pos * 4));
        }
    }
}

/*==============================
WRITE
==============================*/

void GPIO::write(GPIO_TypeDef* port, uint8_t pin, PinState state)
{
    if (state == PinState::Set)
        port->BSRR = (1U << pin);
    else
        port->BSRR = (1U << (pin + 16));
}

/*==============================
READ
==============================*/

PinState GPIO::read(GPIO_TypeDef* port, uint8_t pin)
{
    return (port->IDR & (1U << pin)) ? PinState::Set : PinState::Reset;
}

/*==============================
TOGGLE
==============================*/

void GPIO::toggle(GPIO_TypeDef* port, uint8_t pin)
{
    port->ODR ^= (1U << pin);
}

} // namespace st::gpio