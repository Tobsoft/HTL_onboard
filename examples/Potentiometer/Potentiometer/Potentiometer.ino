#include <HTL_onboard.h>

HTL_onboard htl;

void setup() {
    Serial.begin(9600);
    htl.begin();
}

void loop() {
    // Read the value of the potentiometer
    int potValue = htl.readPot();
    
    // Print the potentiometer value to the serial monitor
    Serial.println(potValue);

    delay(100); // Wait 0.1 Seconds
}
