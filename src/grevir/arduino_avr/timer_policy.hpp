#pragma once

#include <grevir/arduino/pwm.hpp>
#include <grevir/arduino_avr/pin_bindings.hpp>
#include <grevir/base/compat/tuple.hpp>
#include <grevir/core/application.hpp>
#include <grevir/core/board.hpp>
#include <grevir/core/resource_claims.hpp>

namespace ardo::sys {

struct Atmega328pArduinoSignature {};

template <>
struct AvailableTimers<
  Atmega328pArduinoSignature,
  TimerAvailabilityMode::safe_to_use> {
  using Timers = std::tuple<ardo::HardwareTimer<1>, ardo::HardwareTimer<2>>;
};

template <>
struct AvailableTimers<
  Atmega328pArduinoSignature,
  TimerAvailabilityMode::all_available> {
  using Timers = std::tuple<
    ardo::HardwareTimer<0>, ardo::HardwareTimer<1>, ardo::HardwareTimer<2>>;
};

} // namespace ardo::sys

namespace ardo {

/**
 * Arduino millis/micros use Timer0. Applications that need millis must
 * include this module so exclusive Timer0 users fail at compile time.
 */
struct ArduinoMillisClaim {
  using Claims = ResourceClaim<HardwareTimer<0>>;
  static void runSetup() {}
  static void runLoop() {}
};

struct ArduinoMillisReservation : ModuleBase<Parameters<ArduinoMillisClaim>> {};

/**
 * analogWrite plus a shared timer-channel claim. Pins 5 and 6 conflict
 * with ArduinoMillisReservation because they use Timer0.
 */
template <unsigned PIN>
class ArduinoAvrPwm {
public:
  static constexpr unsigned timer = arduino_avr::ArduinoPwmPinTimer<PIN>::value;
  static_assert(timer != 0xFFu, "pin has no Arduino ATmega328P PWM timer");

  using Claims = ResourceClaim<
    GPIOResource<PIN>,
    range_claim<HardwareTimer<timer>, static_cast<int>(PIN)>>;

  static void runSetup() {}
  static void runLoop() {}

  static void setPwm(int value) {
    ArduinoPwm<PIN>::setPwm(value);
  }
};

template <typename... Modules>
using ArduinoAvrApplication = Application<ArduinoMillisReservation, Modules...>;

} // namespace ardo
