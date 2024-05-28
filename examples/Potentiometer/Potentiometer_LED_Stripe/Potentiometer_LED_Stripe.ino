#include <HTL_onboard.h>

HTL_onboard onboard;

void setup() {
    // Initialize the HTL_onboard library
    onboard.begin();
}

void loop() {
    // Read the value from the potentiometer
    int potValue = onboard.readPot();

    // Display the potentiometer value in binary on the LED stripe
    onboard.writeBinary(potValue);

    // Add a small delay to avoid flickering
    delay(100);
}