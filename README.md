# HTL_onboard Library
The HTL_onboard library provides functions to control the onboard hardware components of the HTL Uno development board, including the HEX display, LED stripe, RGB LED, switches, and potentiometer.

## Installation
Download the HTL_onboard library (.zip).
Add the library to your Arduino IDE by navigating to Sketch > Include Library > Add .ZIP Library... and selecting the downloaded ZIP file.

## Usage
## Initialization
```cpp
#include <HTL_onboard.h>

HTL_onboard onboard;

void setup() {
    Serial.begin(9600);
    onboard.begin();
}
```
## Example Programs
### Binary Counting on LED Stripe
```cpp
#include <HTL_onboard.h>

HTL_onboard ledStripe;

void setup() {
    // Initialize the LED-Stripe
    ledStripe.begin();
}

void loop() {
    // Count in binary from 0 to 1023
    for (int i = 0; i < 1024; i++) {
        ledStripe.writeBinary(i);
        delay(50); // Delay for 0.05 seconds (50ms)
    }
}
```

### Decimal and Hexadecimal Counting on HEX-Field
```cpp
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
```

### Reading Switch States
```cpp
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
```

## Documentation

### HTL_onboard Class

#### Public Methods

- `HTL_onboard()`
  - Constructor for the HTL_onboard class.

- `void begin()`
  - Initializes the HTL_onboard library. Sets up pin modes for all necessary pins.

- `void writeHex(int8_t hexNumber)`
  - Writes a hexadecimal number to the HEX display.
  - `hexNumber`: The hexadecimal number to display (-15 to 15).

- `void writeInt(int8_t intNumber)`
  - Writes an integer to the HEX display.
  - `intNumber`: The integer number to display (-19 to 19).

- `void writeBinary(int binValue)`
  - Writes a binary value to the LED stripe.
  - `binValue`: The binary value to display (0 to 1023).

- `void setLED(int pin)`
  - Sets a specific LED on the LED stripe.
  - `pin`: The pin number of the LED to set (0 to 9).

- `void clearLED(int pin)`
  - Clears a specific LED on the LED stripe. This function turns off the specified LED by setting its corresponding pin to HIGH.
  - `pin`: The pin number of the LED to clear (0 to 9).

- `void clearStripe()`
  - Clears all LEDs on the LED stripe (turns them off).

- `void setRGB(uint8_t red, uint8_t green, uint8_t blue)`
  - Sets the RGB LED to the specified color.
  - `red`: The red intensity (0 to 255).
  - `green`: The green intensity (0 to 255).
  - `blue`: The blue intensity (0 to 255).

- `int readSwitchState()`
  - Reads the state of the switches.
  - Returns 2 if switch 2 is pressed, 3 if switch 3 is pressed, 1 if both switches are pressed, and 0 if no switch is pressed.

- `int readPot()`
  - Reads the potentiometer value.
  - Returns the analog value from the potentiometer (0-1023).

- `void setMode(int mode, bool state)`
  - Sets the mode of the HTL_onboard.
  - `mode`: The mode to set (0 for HEX, 1 for LED stripe, 2 for RGB).
  - `state`: The state to set the mode to (true for active, false for inactive).

- `void cfgSwitches(int switch1Threshold, int switch2Threshold, int switch12Min, int switch12Max)`
  - Configures the switch thresholds.
  - `switch1Threshold`: Threshold for switch 1.
  - `switch2Threshold`: Threshold for switch 2.
  - `switch12Min`: Minimum threshold for both switches pressed.
  - `switch12Max`: Maximum threshold for both switches pressed.

## Author
Tobias Weich, 2024