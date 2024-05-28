#include <HTL_onboard.h>

#define MODE_HEX 0
#define MODE_STRIPE 1
#define MODE_RGB 2

#define HEX_UPDATE_INTERVAL 500 // Interval for updating HEX display in milliseconds
#define RGB_UPDATE_INTERVAL 500   // Interval for updating RGB LED in milliseconds
#define STRIPE_UPDATE_INTERVAL 20 // Interval for updating LED stripe in milliseconds

HTL_onboard onboard;

unsigned long lastHexUpdateTime = 0;
unsigned long lastRgbUpdateTime = 0;
unsigned long lastStripeUpdateTime = 0;

void setup() {
    onboard.begin();
    int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
    onboard.setModesMultiplex(activeModes, 3); // Activates HEX and RGB modes
    onboard.setHexMode(HEX_MODE_DEC);
    onboard.setHexNumber(-19);
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
    int nextNumber = onboard.getHexNumber() + 1;
    if (nextNumber > 19) {
      nextNumber = -19;
    }
    onboard.setHexNumber(nextNumber);
}

void updateRgbValues() {
    onboard.setRed(onboard.getRed() + 5);
    onboard.setGreen(onboard.getGreen() + 3);
    onboard.setBlue(onboard.getBlue() + 7);
    if (onboard.getRed() > 255) onboard.setRed(0);
    if (onboard.getGreen() > 255) onboard.setGreen(0);
    if (onboard.getBlue() > 255) onboard.setBlue(0);
}

void updateLedStripeValues() {
    int nextNumber = onboard.getLedStripeValue() + 1;
    if (nextNumber > 1023) {
      nextNumber = 0;
    }
    onboard.setLedStripeValue(nextNumber);
}