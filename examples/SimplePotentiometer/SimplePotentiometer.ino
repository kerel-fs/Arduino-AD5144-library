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
