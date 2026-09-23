#pragma once

namespace ardo::arduino_avr {

/**
 * Arduino pin identity without instantiating AVR MMIO accessors.
 * Port is 'B', 'C' or 'D'; bit is the port bit index.
 */
template <unsigned ArduinoPin, char Port, unsigned Bit>
struct ArduinoAvrPin {
  static constexpr unsigned arduino_pin = ArduinoPin;
  static constexpr char port = Port;
  static constexpr unsigned bit = Bit;
};

} // namespace ardo::arduino_avr
