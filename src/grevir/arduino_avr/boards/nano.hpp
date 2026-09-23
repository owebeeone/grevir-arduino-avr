#pragma once

#include <grevir/arduino_avr/boards/uno.hpp>

namespace ardo::arduino_avr::boards::nano {

// Classic Nano uses the same ATmega328P Arduino 0–19 map as Uno.
using BoardDefinition = uno::BoardDefinition;

} // namespace ardo::arduino_avr::boards::nano
