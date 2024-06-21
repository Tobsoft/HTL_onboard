#include <HTL_onboard.h>

#define HEX_UPDATE_INTERVAL 500 // Interval for updating HEX display in milliseconds
#define RGB_UPDATE_INTERVAL 10   // Interval for updating RGB LED in milliseconds
#define STRIPE_UPDATE_INTERVAL 250 // Interval for updating LED stripe in milliseconds

HTL_onboard onboard;

unsigned long lastHexUpdateTime = 0;
unsigned long lastRgbUpdateTime = 0;
unsigned long lastStripeUpdateTime = 0;

int phase = 0;
int colorIndex = 0;

String str = "HTL Uno   ";

void setup() {
    onboard.begin();
    int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
    onboard.setModesMultiplex(activeModes, 3); // Activates HEX and RGB modes
    onboard.setHexMode(HEX_MODE_STRING);
    onboard.setString(str);
    onboard.setStripeMode(STRIPE_MODE_PROG);
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastHexUpdateTime >= HEX_UPDATE_INTERVAL) {
        lastHexUpdateTime = currentTime;
        updateHexDisplay();
    }

    if (currentTime - lastRgbUpdateTime >= RGB_UPDATE_INTERVAL) {
        lastRgbUpdateTime = currentTime;
        updateRgbValues();
    }

    if (currentTime - lastStripeUpdateTime >= STRIPE_UPDATE_INTERVAL) {
        lastStripeUpdateTime = currentTime;
        updateLedStripeValues();
    }

    onboard.updateMultiplex();
}

void updateHexDisplay() {
  // In String mode, the HEX display gets updated in updateMultiplex()
}

void updateRgbValues() {
    switch (phase) {
        case 0:
            // Gradient transition from red to green
            onboard.setRGB_Multiplex(255 - colorIndex, colorIndex, 0);
            break;
        case 1:
            // Gradient transition from green to blue
            onboard.setRGB_Multiplex(0, 255 - colorIndex, colorIndex);
            break;
        case 2:
            // Gradient transition from blue to red
            onboard.setRGB_Multiplex(colorIndex, 0, 255 - colorIndex);
            break;
    }

    colorIndex++;
    if (colorIndex > 255) {
        colorIndex = 0;
        phase = (phase + 1) % 3; // Move to the next phase
    }
}

void updateLedStripeValues() {
    int nextNumber = onboard.getLedStripeValue() + 1;
    if (nextNumber > 10) {
      nextNumber = 0;
    }
    onboard.setLedStripeValue(nextNumber);
}