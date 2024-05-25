#include <HTL_onboard.h>

HTL_onboard rgbControl;

void setup() {
    // Initialize the RGB LED
    rgbControl.begin();
}

void loop() {
    // Gradient transition from red to green
    for (int i = 0; i <= 255; i++) {
        rgbControl.setRGB(255 - i, i, 0);
        delay(10); // Adjust the delay for speed of the gradient
    }

    // Gradient transition from green to blue
    for (int i = 0; i <= 255; i++) {
        rgbControl.setRGB(0, 255 - i, i);
        delay(10); // Adjust the delay for speed of the gradient
    }

    // Gradient transition from blue to red
    for (int i = 0; i <= 255; i++) {
        rgbControl.setRGB(i, 0, 255 - i);
        delay(10); // Adjust the delay for speed of the gradient
    }
}
