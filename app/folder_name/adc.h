#include "stdint.h"

#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)  // 0x40010000
#define ADC_BASE (APB2PERIPH_BASE + 0x2000UL)         // 0x40012000
#define ADC1 (ADC_BASE + 0x000UL)                     // 0x40012000
#define ADC2 (ADC_BASE + 0x100UL)                     // 0x40012100
#define ADC3 (ADC_BASE + 0x200UL)                     // 0x40012200
#define ADC_COMMON (ADC_BASE + 0x300UL)               // 0x40012300

typedef struct
{
    volatile uint32_t SR;  /* ADC status register,               offset: 0x00 */
    volatile uint32_t CR1; /* ADC control register 1,            offset: 0x04 */
    volatile uint32_t CR2; /* ADC control register 2,            offset: 0x08 */
    volatile uint32_t
        SMPR1; /* ADC sample time register 1,        offset: 0x0C */
    volatile uint32_t
        SMPR2; /* ADC sample time register 2,        offset: 0x10 */
    volatile uint32_t
        JOFR1; /* ADC injected offset register 1,    offset: 0x14 */
    volatile uint32_t
        JOFR2; /* ADC injected offset register 2,    offset: 0x18 */
    volatile uint32_t
        JOFR3; /* ADC injected offset register 3,    offset: 0x1C */
    volatile uint32_t
        JOFR4;             /* ADC injected offset register 4,    offset: 0x20 */
    volatile uint32_t HTR; /* ADC watchdog high threshold,       offset: 0x24 */
    volatile uint32_t LTR; /* ADC watchdog low threshold,        offset: 0x28 */
    volatile uint32_t
        SQR1; /* ADC regular sequence register 1,   offset: 0x2C */
    volatile uint32_t
        SQR2; /* ADC regular sequence register 2,   offset: 0x30 */
    volatile uint32_t
        SQR3; /* ADC regular sequence register 3,   offset: 0x34 */
    volatile uint32_t
        JSQR; /* ADC injected sequence register,    offset: 0x38 */
    volatile uint32_t
        JDR1; /* ADC injected data register 1,      offset: 0x3C */
    volatile uint32_t
        JDR2; /* ADC injected data register 2,      offset: 0x40 */
    volatile uint32_t
        JDR3; /* ADC injected data register 3,      offset: 0x44 */
    volatile uint32_t
        JDR4;             /* ADC injected data register 4,      offset: 0x48 */
    volatile uint32_t DR; /* ADC regular data register,         offset: 0x4C */
} ADC_RegDef_t;

// ADC Common registers — shared by ADC1, ADC2, ADC3
typedef struct
{
    volatile uint32_t CSR; /* ADC common status register,        offset: 0x00 */
    volatile uint32_t CCR; /* ADC common control register,       offset: 0x04 */
    volatile uint32_t CDR; /* ADC common data register,          offset: 0x08 */
} ADC_Common_RegDef_t;

// Clock
