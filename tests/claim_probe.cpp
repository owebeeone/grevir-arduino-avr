#include <GrevirArduinoAVR.h>

#if CASE_ID == 0
using App = ardo::ArduinoAvrApplication<
  ardo::ArduinoParamModule<ardo::arduino::OutputPin<13>>>;
#elif CASE_ID == 1
using App = ardo::ArduinoAvrApplication<
  ardo::ArduinoParamModule<ardo::ArduinoAvrPwm<9>>>;
#elif CASE_ID == 2
using App = ardo::ArduinoAvrApplication<
  ardo::ArduinoParamModule<ardo::ArduinoAvrPwm<5>>>;
#elif CASE_ID == 3
struct ExclusiveTimer0 {
  using Claims = ardo::ResourceClaim<ardo::HardwareTimer<0>>;
  static void runSetup() {}
  static void runLoop() {}
};
using App = ardo::ArduinoAvrApplication<ardo::ArduinoParamModule<ExclusiveTimer0>>;
#elif CASE_ID == 4
struct FirstLed : ardo::ModuleBase<ardo::Parameters<ardo::arduino::OutputPin<13>>> {};
struct SecondLed : ardo::ModuleBase<ardo::Parameters<ardo::arduino::OutputPin<13>>> {};
using App = ardo::ArduinoAvrApplication<FirstLed, SecondLed>;
#else
#error "unknown CASE_ID"
#endif

void instantiate() {
  App::runSetup();
  App::runLoop();
}
