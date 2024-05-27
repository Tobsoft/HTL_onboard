#include <HTL_onboard.h>

HTL_onboard ledStripe;

void setup() {
    // Initialize the LED-Stripe
    ledStripe.begin();
}

void loop() {
    // Count in binary from 0 to 1023
    for (int i = 0; i < 1024; i++) {
        ledStripe.writeBinary(i);
        delay(50); // Delay for 0.05 seconds (50ms)
    }
}