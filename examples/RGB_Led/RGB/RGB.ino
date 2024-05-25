#include <HTL_onboard.h>

HTL_onboard rgbControl;

void setup() {
    // Initialize the RGB LED
    rgbControl.begin();
}

void loop() {
    // Loop through Red, Green, and Blue
    rgbControl.setRGB(255, 0, 0); // Red
    delay(1000);                  // Wait for 1 second

    rgbControl.setRGB(0, 255, 0); // Green
    delay(1000);                  // Wait for 1 second

    rgbControl.setRGB(0, 0, 255); // Blue
    delay(1000);                  // Wait for 1 second
}
