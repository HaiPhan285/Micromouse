#ifndef __GPIO_H__
#define __GPIO_H__
#include <stdint.h>

#define PERIPHERAL_BASE (0x40000000UL)
#define AHB2PERIPH_BASE (PERIPHERAL_BASE + 0x08000000UL)
#define AHB1PERIPH_BASE (PERIPHERAL_BASE + 0x00020000UL)
#define AHB2PERIPH_OFFSET (0x0400UL)

typedef enum
{
    GPIO_port_A = 0,
    GPIO_port_B,
    GPIO_port_C,
    GPIO_port_D,
    GPIO_port_E,
    GPIO_port_F,
    GPIO_port_G,
    GPIO_port_H,
} GPIO_Port_t;

// Define base addresses for GPIO ports using AHB2PERIPH_BASE and AHB2PERIPH_OFFSET
#define GPIO_BASE(port) (AHB2PERIPH_BASE + (uint32_t)(port) * AHB2PERIPH_OFFSET)

#define RCC_BASE (AHB1PERIPH_BASE + 0x00021000UL)

typedef struct
{
    volatile uint32_t CR;        // Clock Control Register - offset 0x00
    volatile uint32_t PLLCFGR;   // PLL Configuration Register - offset 0x04
    volatile uint32_t CFGR;      // Clock Configuration Register - offset 0x08
    volatile uint32_t CIR;       // Clock Interrupt Register - offset 0x0C
    volatile uint32_t AHB1RSTR;  // AHB1 Peripheral Reset Register - offset 0x10
    volatile uint32_t AHB2RSTR;  // AHB2 Peripheral Reset Register - offset 0x14
    volatile uint32_t AHB3RSTR;  // AHB3 Peripheral Reset Register - offset 0x18
    uint32_t RESERVED0;          // Reserved - offset 0x1C
    volatile uint32_t APB1RSTR;  // APB1 Peripheral Reset Register - offset 0x20
    volatile uint32_t APB2RSTR;  // APB2 Peripheral Reset Register - offset 0x24
    uint32_t RESERVED1[2];       // Reserved - offset 0x28-0x2C
    volatile uint32_t
        AHB1ENR;  // AHB1 Peripheral Clock Enable Register - offset 0x30
    volatile uint32_t
        AHB2ENR;  // AHB2 Peripheral Clock Enable Register - offset 0x34
    volatile uint32_t
        AHB3ENR;         // AHB3 Peripheral Clock Enable Register - offset 0x38
    uint32_t RESERVED2;  // Reserved - offset 0x3C
    volatile uint32_t
        APB1ENR;  // APB1 Peripheral Clock Enable Register - offset 0x40
    volatile uint32_t
        APB2ENR;  // APB2 Peripheral Clock Enable Register - offset 0x44
} RCC_RegDef_t;

#define RCC ((RCC_RegDef_t*)RCC_BASE)

//Define bit position for GPIO clock enable in RCC_AHB2ENR register
#define RCC_AHB2ENR_GPIOAEN (1 << 0)  // GPIOA clock enable bit
#define RCC_AHB2ENR_GPIOBEN (1 << 1)  // GPIOB clock enable bit
#define RCC_AHB2ENR_GPIOCEN (1 << 2)  // GPIOC clock enable bit
#define RCC_AHB2ENR_GPIODEN (1 << 3)  // GPIOD clock enable bit
#define RCC_AHB2ENR_GPIOEEN (1 << 4)  // GPIOE clock enable bit
#define RCC_AHB2ENR_GPIOFEN (1 << 5)  // GPIOF clock enable bit
#define RCC_AHB2ENR_GPIOGEN (1 << 6)  // GPIOG clock enable bit
#define RCC_AHB2ENR_GPIOHEN (1 << 7)  // GPIOH clock enable bit

typedef struct
{
    volatile uint32_t MODER;    // Mode Register - offset 0x00
    volatile uint32_t OTYPER;   // Output Type Register - offset 0x04
    volatile uint32_t OSPEEDR;  // Output Speed Register - offset 0x08
    volatile uint32_t PUPDR;    // Pull-up / Pull-down Register - offset 0x0C
    volatile uint32_t IDR;      // Input Data Register - offset 0x10
    volatile uint32_t ODR;      // Output Data Register - offset 0x14
} GPIO_TypeDef_t;

//Define port macros for GPIO and access its structure
#define GPIOA ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_A))
#define GPIOB ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_B))
#define GPIOC ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_C))
#define GPIOD ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_D))
#define GPIOE ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_E))
#define GPIOF ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_F))
#define GPIOG ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_G))
#define GPIOH ((GPIO_TypeDef_t*)GPIO_BASE(GPIO_port_H))

enum class GPIO_PinState_t
{
    RESET = 0,
    SET
};

enum class GPIO_Mode_t
{
    INPUT = 0,
    OUTPUT,
    ALTERNATE,
    ANALOG,
};

enum class GPIO_OType_t
{
    PP = 0,  // Push-Pull
    OD       // Open-Drain
};

enum class GPIO_Speed_t
{
    LOW = 0,
    MEDIUM,
    HIGH,
    VERY_HIGH
};

enum class GPIO_PuPd_t
{
    NOPULL = 0,
    PULLUP,
    PULLDOWN
};

typedef struct
{
    uint16_t pin;        // GPIO pin number (0-15)
    GPIO_Mode_t mode;    // GPIO mode (Input, Output, Alternate, Analog)
    GPIO_OType_t otype;  // Output type (Push-Pull or Open-Drain)
    GPIO_Speed_t speed;  // Output speed
    GPIO_PuPd_t pupd;    // Pull-up / Pull-down
} GPIO_PinConfig_t;

//Function prototypes
void GPIO_ClockEnable(GPIO_TypeDef_t* port);
void GPIO_Init(GPIO_TypeDef_t* port, uint16_t pin, GPIO_PinConfig_t* config);
void GPIO_TogglePin(GPIO_TypeDef_t* port, uint16_t pin);

#endif  // __GPIO_H__