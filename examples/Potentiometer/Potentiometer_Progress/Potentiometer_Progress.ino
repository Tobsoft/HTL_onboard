#include <HTL_onboard.h>

#define potUpdateDelay 100

HTL_onboard onboard;

void setup() {
  onboard.begin();
}

void loop() {
  int value = map(onboard.readPot(), 0, 1020, 0, 10); // get value percentage to potentiometer value
  onboard.writeProgress(value);
  delay(potUpdateDelay);
}