
#include "board.h"
#include "drv8231.h"
#include "enc_math.h"
#include "enc_sample.h"
#include "pid.h"
#include "pid_math.h"
#include "st_timebase.h"
#include "trapezoidal.h"
#include <span>

using namespace MM;

static constexpr float kPi = 3.14159265358979f;
static constexpr float kWheelDiamMm = 14.0f;
static constexpr float kGearRatio = 15.25f;
static constexpr float kTicksPerRev = 12.0f;
static constexpr float kMmPerTick = (kWheelDiamMm * kPi) / (kGearRatio * kTicksPerRev);

static constexpr float kCruiseMmPerSec = 150.0f;
static constexpr float kCruiseTicks = kCruiseMmPerSec / kMmPerTick;

static constexpr float kAccelTicksPerSec2 = 200.0f;
static constexpr float kDecelTicksPerSec2 = 200.0f;

static constexpr float kCellMm = 360.0f;
static constexpr int32_t kCellTicks = static_cast<int32_t>(kCellMm / kMmPerTick);

static void usart_print(Usart& usart, const char* str) {
  usart.send(
      std::span<const uint8_t>(reinterpret_cast<const uint8_t*>(str), __builtin_strlen(str)));
}

int main() {
  bsp_init();
  Board& hw = get_board();

  StTimebaseParams tb_params = {TIM5};
  Stmf4::HwTimebase timebase(tb_params);

  RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
  timebase.init(50'000'000, 1'000'000, std::chrono::microseconds(0xFFFFFFFF));
  timebase.start();
  Utils::bind_timebase(timebase);

  hw.pwm1_left.set_frequency(323);
  hw.pwm2_left.set_frequency(323);
  hw.pwm1_right.set_frequency(323);
  hw.pwm2_right.set_frequency(323);


  const Gains kGains{0.000018f, 0.00000f, 0.000018f};

  PID pid_left(hw.motor_left, kGains);
  PID pid_right(hw.motor_right, kGains);

  Trapezoidal profile;
  profile.configure(0.0f, kCruiseTicks, kAccelTicksPerSec2, kDecelTicksPerSec2, kCellTicks);

  Sample::EncoderTiming timing = Sample::init_encoder_timing(hw.encoder_left, hw.encoder_sample_us);

  usart_print(hw.usart, "time_us,vel_left_mm_s,vel_right_mm_s\r\n");

  unsigned sample_count = 0;

  while (1) {
    const float vel_ticks_left = Sample::sample_encoder(hw.encoder_left, timing);

    const float vel_left = vel_ticks_left;

    [[maybe_unused]] const float ktarget = 4000.0f;
    pid_left.update(ktarget, Drv8231::Direction::FORWARD, static_cast<int32_t>(vel_ticks_left),
                    timing.sample_time_sec);

    if (++sample_count % 5 != 0)
      continue;

    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f\r\n", static_cast<double>(vel_left));
    usart_print(hw.usart, buf);
  }

  hw.motor_left.drive(Drv8231::Direction::COAST, 0);
  hw.motor_right.drive(Drv8231::Direction::COAST, 0);

  usart_print(hw.usart, "== PROFILE COMPLETE ==\r\n");

  while (1) {
  }
}
