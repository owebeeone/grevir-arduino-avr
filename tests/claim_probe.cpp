#include <GrevirArduinoAVR.h>

using Gpio = ardo::sys::avr::arch_atmega328p::GpioBindings<void,void>;
inline constexpr unsigned physical_b1 =
  grevir::pwm::atmega328p::physical_pin<typename Gpio::ppPB1>();
static_assert(ardo::CanonicalGPIO<9>::value == physical_b1);
static_assert(ardo::has_conflict<ardo::GPIOResource<9>,
  ardo::GPIOResource<physical_b1>>::value);
static_assert(!ardo::has_conflict<ardo::GPIOResource<8>,
  ardo::GPIOResource<physical_b1>>::value);

template <typename Claim>
struct ClaimedParameter {
  using Claims = ardo::ResourceClaim<Claim>;
  static void runSetup() {}
  static void runLoop() {}
};

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
#elif CASE_ID == 5
struct BoardOwner : ardo::ModuleBase<ardo::Parameters<ardo::arduino::OutputPin<9>>> {};
struct DeviceOwner : ardo::ModuleBase<ardo::Parameters<ClaimedParameter<
  ardo::GPIOResource<physical_b1>>>> {};
using App = ardo::ArduinoAvrApplication<BoardOwner, DeviceOwner>;
#elif CASE_ID == 6
struct BoardOwner : ardo::ModuleBase<ardo::Parameters<ardo::arduino::OutputPin<8>>> {};
struct DeviceOwner : ardo::ModuleBase<ardo::Parameters<ClaimedParameter<
  ardo::GPIOResource<physical_b1>>>> {};
using App = ardo::ArduinoAvrApplication<BoardOwner, DeviceOwner>;
#else
#error "unknown CASE_ID"
#endif

void instantiate() {
  App::runSetup();
  App::runLoop();
}
