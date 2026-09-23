# Grevir Arduino AVR

Uno/Nano Arduino pin maps, ATmega328P PWM pin-to-timer bindings, and a Timer0
millis reservation. `ArduinoAvrApplication` always claims `HardwareTimer<0>` so
PWM on pins 5 and 6 fails at compile time.

```cpp
#include <GrevirArduinoAVR.h>

using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using App = ardo::ArduinoAvrApplication<ardo::ArduinoParamModule<Led>>;
```

Pin 13 is PORTB bit 5. PWM: 5/6 → Timer0, 9/10 → Timer1, 3/11 → Timer2.
Safe available timers are Timer1 and Timer2. Arduino CLI compile is on weftpi.
