#include <GrevirArduinoAVR.h>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("Uno pin 13 is PORTB bit 5") {
  using Map = ardo::arduino_avr::boards::uno::BoardDefinition::DevicePinMapping::DigitalMap;
  using Pin13 = std::tuple_element_t<13, Map>;
  REQUIRE(Pin13::pin_no == 13);
  REQUIRE(Pin13::PinType::port == 'B');
  REQUIRE(Pin13::PinType::bit == 5);
}

TEST_CASE("Nano map matches Uno for Arduino 0-19") {
  using Uno = ardo::arduino_avr::boards::uno::BoardDefinition::DevicePinMapping::DigitalMap;
  using Nano = ardo::arduino_avr::boards::nano::BoardDefinition::DevicePinMapping::DigitalMap;
  STATIC_REQUIRE(std::tuple_size_v<Uno> == std::tuple_size_v<Nano>);
  using UnoLed = std::tuple_element_t<13, Uno>;
  using NanoLed = std::tuple_element_t<13, Nano>;
  REQUIRE(UnoLed::PinType::port == NanoLed::PinType::port);
  REQUIRE(UnoLed::PinType::bit == NanoLed::PinType::bit);
}

TEST_CASE("Safe timers exclude Timer0") {
  using Safe = ardo::sys::AvailableTimers<
    ardo::sys::Atmega328pArduinoSignature,
    ardo::sys::TimerAvailabilityMode::safe_to_use>::Timers;
  STATIC_REQUIRE(std::tuple_size_v<Safe> == 2);
}

TEST_CASE("AVR PWM writes analogWrite through the Arduino adapter") {
  grevir::arduino::mock::reset();
  ardo::ArduinoAvrPwm<9>::setPwm(80);
  REQUIRE(grevir::arduino::mock::state().analog[9] == 80);
}
