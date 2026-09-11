#include "../board.h"
#include "delay.h"
#include "st_adc.h"
#include "st_dma.h"
#include "st_gpio.h"
#include "st_sys_clk.h"
#include "st_timebase.h"
#include "st_usart.h"

volatile bool g_adc_ovr = false;

namespace {
static constexpr uint32_t kTimerFreq{1'000'000};
static constexpr std::chrono::microseconds kTimerPeriod{100};
}; // namespace

namespace MM {
namespace Stmf4 {
StGpioSettings led_settings{GpioMode::GPOUT, GpioOtype::PUSH_PULL, GpioOspeed::VERY_HIGH,
                            GpioPupd::PULL_DOWN, 0};
StGpioParams led1_params{7, GPIOA, led_settings};
StGpioParams led2_params{6, GPIOA, led_settings};
StGpioParams led3_params{4, GPIOA, led_settings};
StGpioParams led4_params{5, GPIOA, led_settings};
HwGpio led1{led1_params};
HwGpio led2{led2_params};
HwGpio led3{led3_params};
HwGpio led4{led4_params};

StGpioSettings pt_settings{GpioMode::ANALOG, GpioOtype::PUSH_PULL, GpioOspeed::VERY_HIGH,
                           GpioPupd::NO_PULL, 0};
StGpioParams pt1_params{1, GPIOB, pt_settings};
StGpioParams pt2_params{0, GPIOB, pt_settings};
StGpioParams pt3_params{1, GPIOC, pt_settings};
StGpioParams pt4_params{0, GPIOC, pt_settings};
HwGpio pt1{pt1_params};
HwGpio pt2{pt2_params};
HwGpio pt3{pt3_params};
HwGpio pt4{pt4_params};

StDmaSettings dma_settings{DmaChSel::CH0, DmaPriority::VERY_HIGH, DmaWidth::HALF_WORD,
                           DmaDataDir::PERIPH_TO_MEM};
StDmaParams dma_params{dma_settings, DMA2, DMA2_Stream0,
                       static_cast<uint32_t>(reinterpret_cast<std::uintptr_t>(&ADC1->DR))};
HwDma dma{dma_params};

std::array<uint8_t, 1> adc_seq{9};
AdcChCycles ch9_cycles{9, AdcCycles::CYCLES_144};
AdcChCycles ch8_cycles{8, AdcCycles::CYCLES_144};
AdcChCycles ch11_cycles{11, AdcCycles::CYCLES_144};
AdcChCycles ch10_cycles{10, AdcCycles::CYCLES_144};
std::array<AdcChCycles, 4> adc_ch_cycles{ch9_cycles, ch8_cycles, ch11_cycles, ch10_cycles};
StAdcSettings adc_settings{AdcResolution::TWELVE_BIT,
                           AdcClkPrescaler::PCLK2_DIV_2,
                           AdcTriggerSource::SOFTWARE,
                           AdcOverrunInt::OVRIE_EN,
                           AdcDma::DMA_ENABLE,
                           adc_seq,
                           adc_ch_cycles};
StAdcParams adc_params{adc_settings, ADC1, ADC1_COMMON};
HwAdc adc{adc_params};

IrParams ir1_params{adc, dma, led1, 9};
IrParams ir2_params{adc, dma, led2, 8};
IrParams ir3_params{adc, dma, led3, 11};
IrParams ir4_params{adc, dma, led4, 10};
IrSensor ir1{ir1_params};
IrSensor ir2{ir2_params};
IrSensor ir3{ir3_params};
IrSensor ir4{ir4_params};

std::array<IrSensor*, 4> ir_sequence{&ir1, &ir2, &ir3, &ir4};
IrValues ir_vals{};
IrControllerParams ircontroller_params{ir_sequence, ir_vals};
IrController ircontroller{ircontroller_params};

StTimebaseParams timebase_params{TIM1};
HwTimebase timebase{timebase_params};

HwClk clk{Configuration::SYSCLK_HSE_100MHZ};

StGpioSettings usart_gpio_settings{GpioMode::AF, GpioOtype::PUSH_PULL, GpioOspeed::VERY_HIGH,
                                   GpioPupd::NO_PULL, 7};
StGpioParams usart_tx_params{9, GPIOA, usart_gpio_settings};  // PA9  USART1_TX AF7
StGpioParams usart_rx_params{10, GPIOA, usart_gpio_settings}; // PA10 USART1_RX AF7
HwGpio usart_tx{usart_tx_params};
HwGpio usart_rx{usart_rx_params};
StUsartSettings usart_settings{UsartOversample::X8, UsartSampleMode::SINGLE};
StUsartParams usart_params{USART1, clk.get_freq(), 115200, usart_settings};
StUsart usart{usart_params};

StTimebaseParams delay_params{TIM5};
HwTimebase delay{delay_params};

} // namespace Stmf4
} // namespace MM

namespace MM {
Board board{.ir_controller = MM::Stmf4::ircontroller,
            .timebase = MM::Stmf4::timebase,
            .usart = MM::Stmf4::usart,
            .delay = MM::Stmf4::delay};

bool board_init() {
  bool result = true;

  result = result && Stmf4::clk.init();
  result = result && Stmf4::usart.set_clock_freq(Stmf4::clk.get_freq());
  uint32_t hclk = Stmf4::clk.get_freq();
  uint32_t tim_pclk = hclk / 2u;

  RCC->AHB1ENR |=
      (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_DMA2EN);
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  RCC->APB2ENR |= (RCC_APB2ENR_ADC1EN | RCC_APB2ENR_TIM1EN);
  RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

  result = result && Stmf4::led1.init();
  result = result && Stmf4::led2.init();
  result = result && Stmf4::led3.init();
  result = result && Stmf4::led4.init();

  result = result && Stmf4::pt1.init();
  result = result && Stmf4::pt2.init();
  result = result && Stmf4::pt3.init();
  result = result && Stmf4::pt4.init();

  result = result && Stmf4::dma.init();
  result = result && Stmf4::adc.init();
  result = result && Stmf4::usart_tx.init();
  result = result && Stmf4::usart_rx.init();
  result = result && Stmf4::usart.init();
  if (result) {
    static constexpr uint8_t kBootMsg[] = "BOOT\r\n";
    Stmf4::usart.send(std::span<const uint8_t>(kBootMsg, sizeof(kBootMsg) - 1));
  }
  result = result && Stmf4::timebase.init(tim_pclk, kTimerFreq, kTimerPeriod, true);
  if (!result) {
    return false;
  }

  Stmf4::timebase.start();

  result &= Stmf4::delay.init(50'000'000u, 1'000'000u, std::chrono::microseconds(4'294'967u));
  Stmf4::delay.start();

  Utils::bind_timebase(Stmf4::delay);

  NVIC_EnableIRQ(ADC_IRQn);
  NVIC_SetPriority(ADC_IRQn, 0);

  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
  NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0);

  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_SetPriority(USART1_IRQn, 1);

  return result;
}

void board_recover() {
  bool result = true;

  NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);

  Stmf4::adc.stop();

  result = result && Stmf4::dma.abort();

  result = result && Stmf4::adc.ovr_recover();
  result = result && Stmf4::adc.en_dma_req();

  Stmf4::led1.set(0);
  Stmf4::led2.set(0);
  Stmf4::led3.set(0);
  Stmf4::led4.set(0);

  result = result && Stmf4::ircontroller.reset();

  if (!result) {
    g_adc_ovr = true;
    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    return;
  }

  g_adc_ovr = false;

  NVIC_EnableIRQ(ADC_IRQn);
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

Board& get_board() {
  return board;
}

extern "C" void ADC_IRQHandler() {
  g_adc_ovr = true;
  NVIC_DisableIRQ(ADC_IRQn);
}

extern "C" void USART1_IRQHandler(void) {
  if (Stmf4::usart.get_addr()->SR & USART_SR_RXNE) {
    if (board.usart.receive(rx_byte)) {
      std::span<const uint8_t> tx_span(&rx_byte, 1);
      board.usart.send(tx_span);
    }
  }
}

extern "C" void TIM1_UP_TIM10_IRQHandler() {
  TIM1->SR &= ~TIM_SR_UIF;

  if (g_adc_ovr) {
    board_recover();
    return;
  }

  Stmf4::ircontroller.update();
}
} // namespace MM