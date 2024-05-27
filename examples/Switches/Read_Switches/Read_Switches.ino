#include <HTL_onboard.h>

HTL_onboard switchReader;

void setup() {
    Serial.begin(9600);
    switchReader.begin();
}

void loop() {
    // Read the state of the switches
    int switchState = switchReader.readSwitchState();

    // Print the switch state
    if (switchState == 3) {
        Serial.println("Switch 3 is active");
    } else if (switchState == 2) {
        Serial.println("Switch 2 is active");
    } else if (switchState == 1) {
      Serial.println("Both Switches are active");
    } else {
        Serial.println("No switches are active");
    }

    Serial.println(analogRead(A1));

    delay(1000); // Delay for 1 second
}