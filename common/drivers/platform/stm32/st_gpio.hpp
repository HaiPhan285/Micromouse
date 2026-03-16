#ifndef ST_GPIO_HPP
#define ST_GPIO_HPP

#include <stdint.h>
#include "stm32f4xx.h"
namespace st::gpio
{

enum class Mode : uint8_t
{
    Input = 0,
    Output = 1,
    Alternate = 2,
    Analog = 3
};

enum class OutputType : uint8_t
{
    PushPull = 0,
    OpenDrain = 1
};

enum class Speed : uint8_t
{
    Low = 0,
    Medium = 1,
    High = 2,
    VeryHigh = 3
};

enum class Pull : uint8_t
{
    None = 0,
    PullUp = 1,
    PullDown = 2
};

enum class PinState : uint8_t
{
    Reset = 0,
    Set = 1
};

struct PinConfig
{
    uint8_t pin;
    Mode mode;
    OutputType otype;
    Speed speed;
    Pull pull;
    uint8_t alternate;
};

class GPIO
{
public:

    static void enableClock(GPIO_TypeDef* port);

    static void init(GPIO_TypeDef* port, const PinConfig& config);

    static void write(GPIO_TypeDef* port, uint8_t pin, PinState state);

    static PinState read(GPIO_TypeDef* port, uint8_t pin);

    static void toggle(GPIO_TypeDef* port, uint8_t pin);
};

}

#endif