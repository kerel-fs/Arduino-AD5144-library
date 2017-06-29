# AD5144 Arduino library

This driver interfaces the microcontroller with Analog Devices AD5144 digital potentiometer via SPI.

## Usage
```
#include "AD5144.h"

AD5144 poti;

void setup() {
  poti.begin();
  Serial.begin(9600);
}

void loop() {
  poti.set_value(0, (millis() / 1000) % 256);
  Serial.println(poti.get_value(0));

  delay(1000);
}
```

# License

This library is licensed under the GNU Lesser General Public License v3.0 or later.
