#pragma once

#include <grevir/arduino_avr/pin_identity.hpp>
#include <grevir/base/compat/cstdint.hpp>
#include <grevir/base/compat/tuple.hpp>
#include <grevir/core/device_map.hpp>

namespace ardo::arduino_avr::boards::uno {

using ardo::arduino_avr::ArduinoAvrPin;

struct BoardDefinition {
  static constexpr std::uint32_t CPU_FREQUENCY_HZ = 16000000L;

  using DevicePinMapping = setl::DeviceMappings<
    std::tuple<
      setl::PortMapping<ArduinoAvrPin<0, 'D', 0>, 0>,
      setl::PortMapping<ArduinoAvrPin<1, 'D', 1>, 1>,
      setl::PortMapping<ArduinoAvrPin<2, 'D', 2>, 2>,
      setl::PortMapping<ArduinoAvrPin<3, 'D', 3>, 3>,
      setl::PortMapping<ArduinoAvrPin<4, 'D', 4>, 4>,
      setl::PortMapping<ArduinoAvrPin<5, 'D', 5>, 5>,
      setl::PortMapping<ArduinoAvrPin<6, 'D', 6>, 6>,
      setl::PortMapping<ArduinoAvrPin<7, 'D', 7>, 7>,
      setl::PortMapping<ArduinoAvrPin<8, 'B', 0>, 8>,
      setl::PortMapping<ArduinoAvrPin<9, 'B', 1>, 9>,
      setl::PortMapping<ArduinoAvrPin<10, 'B', 2>, 10>,
      setl::PortMapping<ArduinoAvrPin<11, 'B', 3>, 11>,
      setl::PortMapping<ArduinoAvrPin<12, 'B', 4>, 12>,
      setl::PortMapping<ArduinoAvrPin<13, 'B', 5>, 13>,
      setl::PortMapping<ArduinoAvrPin<14, 'C', 0>, 14>,
      setl::PortMapping<ArduinoAvrPin<15, 'C', 1>, 15>,
      setl::PortMapping<ArduinoAvrPin<16, 'C', 2>, 16>,
      setl::PortMapping<ArduinoAvrPin<17, 'C', 3>, 17>,
      setl::PortMapping<ArduinoAvrPin<18, 'C', 4>, 18>,
      setl::PortMapping<ArduinoAvrPin<19, 'C', 5>, 19>
    >
  >;
};

} // namespace ardo::arduino_avr::boards::uno
