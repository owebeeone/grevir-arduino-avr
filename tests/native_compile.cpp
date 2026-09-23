#include <GrevirArduinoAVR.h>

namespace {
using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using Pwm9 = ardo::ArduinoAvrPwm<9>;
using App = ardo::ArduinoAvrApplication<ardo::ArduinoParamModule<Led, Pwm9>>;

using Pin13 = std::tuple_element_t<13,
  ardo::arduino_avr::boards::uno::BoardDefinition::DevicePinMapping::DigitalMap>;
}

static_assert(ardo::arduino_avr::ArduinoPwmPinTimer<5>::value == 0);
static_assert(ardo::arduino_avr::ArduinoPwmPinTimer<6>::value == 0);
static_assert(ardo::arduino_avr::ArduinoPwmPinTimer<9>::value == 1);
static_assert(ardo::arduino_avr::ArduinoPwmPinTimer<10>::value == 1);
static_assert(ardo::arduino_avr::ArduinoPwmPinTimer<3>::value == 2);
static_assert(ardo::arduino_avr::ArduinoPwmPinTimer<11>::value == 2);
static_assert(Pin13::PinType::arduino_pin == 13);
static_assert(Pin13::PinType::port == 'B');
static_assert(Pin13::PinType::bit == 5);
static_assert(ardo::arduino_avr::SelectedBoard::CPU_FREQUENCY_HZ == 16000000L);

void instantiate_arduino_avr() {
  App::runSetup();
  App::runLoop();
  Pwm9::setPwm(40);
}
