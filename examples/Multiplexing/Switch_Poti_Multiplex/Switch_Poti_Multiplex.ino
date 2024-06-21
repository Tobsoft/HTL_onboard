#include <HTL_onboard.h>

// Create an instance of the HTL_onboard class
HTL_onboard onboard;

// Only update LED stripe every now and then, because the potentiometer tends to float.
// Doing this will reduce flickering in the LSB

// Variable to store the last time the LED stripe was updated
unsigned long lastUpdateTime = 0;
// Update interval for the LED stripe (in milliseconds)
const unsigned long updateInterval = 100;

void setup() {
    // Initialize the HTL_onboard library
    onboard.begin();

    // Define active modes for multiplexing (HEX display and LED stripe)
    int activeModes[] = {MODE_HEX, MODE_STRIPE};

    // Set the modes for multiplexing
    onboard.setModesMultiplex(activeModes, 2);

    // Set the multiplexing interval (in milliseconds)
    onboard.setMultiplexInterval(1); // Change interval as needed
}

void loop() {
    // Check if it's time to update the LED stripe
    unsigned long currentTime = millis();
    if (currentTime - lastUpdateTime >= updateInterval) {
        // Read the value from the potentiometer
        int potValue = onboard.readPot();
        // If reading is close to maximum, display all leds on
        if (potValue >= 1022) {
          potValue = 1023;
        }

        // Display the potentiometer value in binary on the LED stripe
        onboard.setLedStripeValue(potValue);

        // Update the last update time
        lastUpdateTime = currentTime;
    }

    // Display the switch state on the HEX display
    onboard.setHexNumber(onboard.readSwitchState());

    // Update multiplexing to alternate between modes
    onboard.updateMultiplex();
}