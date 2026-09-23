#define GREVIR_ARDUINO_HOST_MOCK
#include <GrevirArduinoAVR.h>
#include <tuple>

using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using App = ardo::ArduinoAvrApplication<ardo::ArduinoParamModule<Led>>;

int main() {
  App::runSetup();
  App::runLoop();
  using Map = ardo::arduino_avr::SelectedBoard::DevicePinMapping::DigitalMap;
  using Pin13 = std::tuple_element_t<13, Map>;
  if (Pin13::PinType::port != 'B' || Pin13::PinType::bit != 5) {
    return 1;
  }
  return 0;
}
