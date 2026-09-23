#pragma once

#include <grevir/arduino_avr/boards/nano.hpp>

namespace ardo::arduino_avr::boards::nano_old_bootloader {

// Same pin map; FQBN differs only in bootloader/upload protocol.
using BoardDefinition = nano::BoardDefinition;

} // namespace ardo::arduino_avr::boards::nano_old_bootloader
