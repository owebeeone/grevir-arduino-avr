#pragma once

#include <grevir/arduino_avr/boards/nano.hpp>
#include <grevir/arduino_avr/boards/nano_old_bootloader.hpp>
#include <grevir/arduino_avr/boards/uno.hpp>
#include <grevir/arduino_avr/timer_policy.hpp>
#include <grevir/core/board.hpp>

namespace ardo::arduino_avr {

#if defined(ARDUINO_AVR_NANO)
using SelectedBoard = boards::nano::BoardDefinition;
#elif defined(ARDUINO_AVR_NANO_OLD)
using SelectedBoard = boards::nano_old_bootloader::BoardDefinition;
#else
using SelectedBoard = boards::uno::BoardDefinition;
#endif

} // namespace ardo::arduino_avr

namespace ardo::sys {

template <>
struct IOMapping<Atmega328pArduinoSignature, BoardType::arduino_uno> {
  using mapping = arduino_avr::boards::uno::BoardDefinition::DevicePinMapping;
};

template <>
struct IOMapping<Atmega328pArduinoSignature, BoardType::arduino_nano> {
  using mapping = arduino_avr::boards::nano::BoardDefinition::DevicePinMapping;
};

} // namespace ardo::sys
