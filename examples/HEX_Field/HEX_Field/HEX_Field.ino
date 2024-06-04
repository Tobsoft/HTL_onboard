#include <HTL_onboard.h>

HTL_onboard hexPanel;

void setup() {
    // Initialize the Hex Field
    hexPanel.begin();
}

void loop() {
    // Display hexadecimal numbers from -F to F
    for (int i = -15; i <= 15; i++) {
        hexPanel.writeHex(i);
        delay(500); // Delay for 0.5 seconds
    }

    // Display Integer Values from -19 to 19
    for (int i = -19; i <= 19; i++) {
      hexPanel.writeInt(i);
      delay(500);
    }
}
