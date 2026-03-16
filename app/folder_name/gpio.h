#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*==============================================================================
 * BASE ADDRESSES
 *============================================================================*/
#define PERIPH_BASE 0x40000000UL
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)

#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOF_BASE (AHB1PERIPH_BASE + 0x1400UL)
#define GPIOG_BASE (AHB1PERIPH_BASE + 0x1800UL)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00UL)

#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)

/*==============================================================================
 * RCC AHB1ENR REGISTER (Clock Enable)
 *============================================================================*/
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;  // AHB1 peripheral clock enable register
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_RegDef_t;

#define RCC ((RCC_RegDef_t*)RCC_BASE)

/* RCC AHB1ENR bit positions */
#define RCC_AHB1ENR_GPIOAEN (1U << 0)
#define RCC_AHB1ENR_GPIOBEN (1U << 1)
#define RCC_AHB1ENR_GPIOCEN (1U << 2)
#define RCC_AHB1ENR_GPIODEN (1U << 3)
#define RCC_AHB1ENR_GPIOEEN (1U << 4)
#define RCC_AHB1ENR_GPIOFEN (1U << 5)
#define RCC_AHB1ENR_GPIOGEN (1U << 6)
#define RCC_AHB1ENR_GPIOHEN (1U << 7)

/*==============================================================================
 * GPIO REGISTER DEFINITION
 *============================================================================*/
typedef struct
{
    volatile uint32_t
        MODER; /*!< GPIO port mode register,               offset: 0x00 */
    volatile uint32_t
        OTYPER; /*!< GPIO port output type register,        offset: 0x04 */
    volatile uint32_t
        OSPEEDR; /*!< GPIO port output speed register,       offset: 0x08 */
    volatile uint32_t
        PUPDR; /*!< GPIO port pull-up/pull-down register,  offset: 0x0C */
    volatile uint32_t
        IDR; /*!< GPIO port input data register,         offset: 0x10 */
    volatile uint32_t
        ODR; /*!< GPIO port output data register,        offset: 0x14 */
    volatile uint32_t
        BSRR; /*!< GPIO port bit set/reset register,      offset: 0x18 */
    volatile uint32_t
        LCKR; /*!< GPIO port configuration lock register, offset: 0x1C */
    volatile uint32_t
        AFR[2]; /*!< GPIO alternate function registers,     offset: 0x20-0x24 */
} GPIO_RegDef_t;

/* GPIO Port Macros */
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASE)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASE)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASE)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASE)

/*==============================================================================
 * GPIO CONFIGURATION ENUMS
 *============================================================================*/

/** @brief GPIO Pin Modes */
typedef enum
{
    GPIO_MODE_INPUT = 0x00U,  /*!< Input mode                  */
    GPIO_MODE_OUTPUT = 0x01U, /*!< General purpose output mode */
    GPIO_MODE_AF = 0x02U,     /*!< Alternate function mode     */
    GPIO_MODE_ANALOG = 0x03U  /*!< Analog mode                 */
} GPIO_Mode_t;

/** @brief GPIO Output Types */
typedef enum
{
    GPIO_OTYPE_PP = 0x00U, /*!< Push-pull output  */
    GPIO_OTYPE_OD = 0x01U  /*!< Open-drain output */
} GPIO_OType_t;

/** @brief GPIO Output Speed */
typedef enum
{
    GPIO_SPEED_LOW = 0x00U,    /*!< Low speed       */
    GPIO_SPEED_MEDIUM = 0x01U, /*!< Medium speed    */
    GPIO_SPEED_FAST = 0x02U,   /*!< Fast speed      */
    GPIO_SPEED_HIGH = 0x03U    /*!< High speed      */
} GPIO_Speed_t;

/** @brief GPIO Pull-up / Pull-down */
typedef enum
{
    GPIO_PUPD_NONE = 0x00U, /*!< No pull-up or pull-down */
    GPIO_PUPD_PU = 0x01U,   /*!< Pull-up                 */
    GPIO_PUPD_PD = 0x02U    /*!< Pull-down               */
} GPIO_PuPd_t;

/** @brief GPIO Pin State */
typedef enum
{
    GPIO_PIN_RESET = 0U,
    GPIO_PIN_SET = 1U
} GPIO_PinState_t;

/** @brief GPIO Alternate Functions (AF0–AF15 for STM32F446RE) */
typedef enum
{
    GPIO_AF0 = 0x00U,  /*!< SYS / MCO / JTAG / SWD  */
    GPIO_AF1 = 0x01U,  /*!< TIM1 / TIM2              */
    GPIO_AF2 = 0x02U,  /*!< TIM3 / TIM4 / TIM5       */
    GPIO_AF3 = 0x03U,  /*!< TIM8 / TIM9 / TIM10 /TIM11 */
    GPIO_AF4 = 0x04U,  /*!< I2C1 / I2C2 / I2C3       */
    GPIO_AF5 = 0x05U,  /*!< SPI1 / SPI2 / SPI3 / SPI4 */
    GPIO_AF6 = 0x06U,  /*!< SAI1                     */
    GPIO_AF7 = 0x07U,  /*!< USART1 / USART2 / USART3 */
    GPIO_AF8 = 0x08U,  /*!< USART6 / UART4 / UART5   */
    GPIO_AF9 = 0x09U,  /*!< CAN1 / CAN2 / TIM12/13/14 */
    GPIO_AF10 = 0x0AU, /*!< OTG_FS / OTG_HS          */
    GPIO_AF11 = 0x0BU, /*!< ETH                      */
    GPIO_AF12 = 0x0CU, /*!< FMC / SDIO / OTG_HS      */
    GPIO_AF13 = 0x0DU, /*!< DCMI                     */
    GPIO_AF14 = 0x0EU, /*!< Reserved                 */
    GPIO_AF15 = 0x0FU  /*!< EVENTOUT                 */
} GPIO_AF_t;

/*==============================================================================
 * GPIO PIN CONFIGURATION STRUCTURE
 *============================================================================*/
typedef struct
{
    uint8_t pin;        /*!< Pin number: 0–15              */
    GPIO_Mode_t mode;   /*!< Pin mode                      */
    GPIO_OType_t otype; /*!< Output type                   */
    GPIO_Speed_t speed; /*!< Output speed                  */
    GPIO_PuPd_t pupd;   /*!< Pull-up / Pull-down selection */
    GPIO_AF_t af;       /*!< Alternate function (if AF mode) */
} GPIO_PinConfig_t;

/*==============================================================================
 * FUNCTION PROTOTYPES
 *============================================================================*/
void GPIO_ClockEnable(GPIO_RegDef_t* port);
void GPIO_Init(GPIO_RegDef_t* port, GPIO_PinConfig_t* config);
void GPIO_DeInit(GPIO_RegDef_t* port, uint8_t pin);
void GPIO_WritePin(GPIO_RegDef_t* port, uint8_t pin, GPIO_PinState_t state);
GPIO_PinState_t GPIO_ReadPin(GPIO_RegDef_t* port, uint8_t pin);
void GPIO_TogglePin(GPIO_RegDef_t* port, uint8_t pin);
void GPIO_SetAF(GPIO_RegDef_t* port, uint8_t pin, GPIO_AF_t af);

#endif /* GPIO_H */