#include <HTL_onboard.h>

HTL_onboard switchReader;

void setup() {
    switchReader.begin();
}

void loop() {
    // Read the state of the switches
    int switchState = switchReader.readSwitchState();

    // Print the switch state to HEX field
    switchReader.writeHex(switchState);

    delay(50); // Delay for 0.05 seconds
}
