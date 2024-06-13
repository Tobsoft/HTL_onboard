#include <HTL_onboard.h>

HTL_onboard onboard;

unsigned long lastHexUpdateTime = 0;

String message = "HTL Uno   "; // It's good to add ~3 spaces to the end of the message, this adds a pause in the loop.

void setup() {
    onboard.begin();
    int activeModes[] = {MODE_HEX};
    onboard.setModesMultiplex(activeModes, 1); // Activates HEX and RGB modes
    onboard.setHexMode(HEX_MODE_STRING);
    onboard.setString(message);
}

void loop() {
    onboard.updateMultiplex();
}