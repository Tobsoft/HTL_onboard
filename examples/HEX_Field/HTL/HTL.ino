#include <HTL_onboard.h>
#include <string.h>

#define DISPLAY_DELAY 500  // Delay time in milliseconds

// Create an instance of the HTL_onboard class
HTL_onboard onboard;

String message = "HTL Uno   ";

void setup() {
    // Initialize the HTL_onboard library
    onboard.begin();
}

void loop() {
    for (int i = 0; i < message.length(); i++) {
      onboard.writeChar(message[i]);
      delay(DISPLAY_DELAY);
    }
}