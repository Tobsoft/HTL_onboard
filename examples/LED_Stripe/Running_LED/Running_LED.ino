#include <HTL_onboard.h>

HTL_onboard ledStripe;

void setup() {
    // Initialize the LED-Stripe
    ledStripe.begin();
    ledStripe.clearStripe(); // Ensure all LEDs are off at the start
}

void loop() {
    // Create a running LED effect
    // Run Forwards
    for (int i = 0; i < 10; i++) {
        ledStripe.clearStripe();  // Turn off all LEDs
        ledStripe.setLED(i);      // Turn on the current LED
        delay(200);               // Wait for 200 milliseconds
    }

    // Comment out to run only in one direction and reset at the end
    // Run Backwards
    for (int i = 8; i > 0; i--) {
        ledStripe.clearStripe();  // Turn off all LEDs
        ledStripe.setLED(i);      // Turn on the current LED
        delay(200);               // Wait for 200 milliseconds
    }
}
