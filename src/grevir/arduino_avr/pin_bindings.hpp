#pragma once

namespace ardo::arduino_avr {

/**
 * Arduino ATmega328P PWM pin → hardware timer.
 * 5/6 → Timer0, 9/10 → Timer1, 3/11 → Timer2.
 */
template <unsigned PIN>
struct ArduinoPwmPinTimer {
  static constexpr unsigned value = 0xFFu;
};

template <> struct ArduinoPwmPinTimer<3> { static constexpr unsigned value = 2; };
template <> struct ArduinoPwmPinTimer<5> { static constexpr unsigned value = 0; };
template <> struct ArduinoPwmPinTimer<6> { static constexpr unsigned value = 0; };
template <> struct ArduinoPwmPinTimer<9> { static constexpr unsigned value = 1; };
template <> struct ArduinoPwmPinTimer<10> { static constexpr unsigned value = 1; };
template <> struct ArduinoPwmPinTimer<11> { static constexpr unsigned value = 2; };

} // namespace ardo::arduino_avr
