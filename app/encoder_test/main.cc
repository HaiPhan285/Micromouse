#include <numbers>

#include "board.h"

namespace {
constexpr float kWheelDiameterCm{1.4f};
constexpr float kGearRatio{15.0f};
constexpr float kCountsPerMotorTurn{12.0f};
constexpr uint32_t kSamplePeriodUs{100'000};
constexpr float kCountsPerWheelTurn{kGearRatio * kCountsPerMotorTurn};
constexpr float kTravelPerCount{kWheelDiameterCm * std::numbers::pi_v<float> / kCountsPerWheelTurn};

void exposeForDebugger(const MM::EncoderStats& stats) {
  volatile float rpm{stats.rpm};
  volatile float velocity{stats.velocity_cm_per_sec};
  volatile float distance{stats.distance_cm};
  volatile float elapsed{stats.delta_time_sec};
  volatile int32_t ticks{stats.delta_ticks};
  (void)rpm;
  (void)velocity;
  (void)distance;
  (void)elapsed;
  (void)ticks;
}
} // namespace

int main() {
  if (!MM::bsp_init()) {
    return 1;
  }

  MM::Encoder& encoder{MM::get_board().encoder};
  encoder.init_cycle_counter();
  const uint32_t sample_cycles{kSamplePeriodUs * encoder.cycles_per_us()};

  for (;;) {
    const MM::EncoderStats stats{
        encoder.measure_encoder_stats(sample_cycles, kCountsPerWheelTurn, kTravelPerCount)};
    exposeForDebugger(stats);
  }
}
