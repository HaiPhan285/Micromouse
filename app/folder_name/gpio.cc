#include "gpio.h"
#include <stdint.h>

using namespace std;

void GPIO_ClockEnable(GPIO_TypeDef_t* port)
{
    // Enable the clock for the specified GPIO port
    RCC->AHB2ENR |= (1U << (uint32_t)port);
}
void GPIO_Init(GPIO_TypeDef_t* port, uint16_t pin, GPIO_PinConfig_t* config)
{
    GPIO_ClockEnable(port);  // Enable the clock for the specified GPIO port
    // Configure the GPIO pin mode
    port->MODER &= ~(3 << (pin * 2));                                   // Clear
    port->MODER |= (static_cast<uint32_t>(config->mode) << (pin * 2));  // Set

    //Confifure the output type
    port->OTYPER &= ~(1 << pin);                                    // Clear
    port->OTYPER |= (static_cast<uint32_t>(config->otype) << pin);  // Set

    //Configure speed
    port->OSPEEDR &= ~(3 << (pin * 2));  // Clear
    port->OSPEEDR |=
        (static_cast<uint32_t>(config->speed) << (pin * 2));  // Set

    //Configure pullup/pulldown
    port->PUPDR &= ~(3 << (pin * 2));                                   //Clear
    port->PUPDR |= (static_cast<uint32_t>(config->pupd) << (pin * 2));  // Set
}

void GPIO_TogglePin(GPIO_TypeDef_t* port, uint16_t pin)
{
    port->ODR ^= (1 << pin);
}