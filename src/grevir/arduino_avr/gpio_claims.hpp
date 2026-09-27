#pragma once

#include <grevir/arduino_avr/selected_board.hpp>
#include <grevir/avr/devices/atmega328p/pwm_candidates.hpp>
#include <grevir/core/resource_claims.hpp>
#include <grevir/base/compat/tuple.hpp>

namespace ardo::arduino_avr::nfp {

template <typename Map, unsigned Pin, std::size_t Index = 0>
consteval unsigned canonical_pin() {
  if constexpr (Index == std::tuple_size_v<Map>) {
    return Pin;
  } else {
    using Entry = std::tuple_element_t<Index,Map>;
    if constexpr (Entry::pin_no == Pin) {
      using BoardPin = typename Entry::PinType;
      if constexpr (BoardPin::port == 'B') {
        return grevir::pwm::atmega328p::physical_pin<
          ardo::sys::avr::arch_atmega328p::rrPORTB,BoardPin::bit>();
      } else if constexpr (BoardPin::port == 'C') {
        return grevir::pwm::atmega328p::physical_pin<
          ardo::sys::avr::arch_atmega328p::rrPORTC,BoardPin::bit>();
      } else if constexpr (BoardPin::port == 'D') {
        return grevir::pwm::atmega328p::physical_pin<
          ardo::sys::avr::arch_atmega328p::rrPORTD,BoardPin::bit>();
      } else {
        static_assert(BoardPin::port == 'B' || BoardPin::port == 'C'
          || BoardPin::port == 'D', "GREVIR_AVR_UNKNOWN_BOARD_PORT");
        return 0;
      }
    } else {
      return canonical_pin<Map,Pin,Index + 1>();
    }
  }
}

} // namespace ardo::arduino_avr::nfp

namespace ardo {

template <unsigned P> requires (P < 20)
struct CanonicalGPIO<P> {
  using Map = typename arduino_avr::SelectedBoard::DevicePinMapping::DigitalMap;
  static constexpr unsigned value = arduino_avr::nfp::canonical_pin<Map,P>();
};

} // namespace ardo
