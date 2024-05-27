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

## Multiplex Mode Usage

The HTL_onboard library supports multiplexing between different display modes, including HEX display, LED stripe, and RGB LED. Multiplexing allows you to cycle through these modes in a time-sharing manner, enabling multiple outputs to be shown on a single display sequentially. This section will guide you on how to use the multiplex mode.

### Step-by-Step Guide

1. **Initialization**
   Initialize the HTL_onboard library in your `setup()` function. This sets up the pin modes for all necessary pins.

    ```cpp
    HTL_onboard onboard;

    void setup() {
        onboard.begin();
    }
    ```

2. **Set Active Modes for Multiplexing**
   Define which modes you want to include in the multiplexing operation. Use the `setModesMultiplex` function to specify the active modes. The modes should be specified using their corresponding constants: `MODE_HEX`, `MODE_STRIPE`, and `MODE_RGB`.

    ```cpp
    void setup() {
        onboard.begin();
        int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
        onboard.setModesMultiplex(activeModes, 3); // Activate HEX, RGB, and LED stripe modes
    }
    ```

3. **Set Multiplex Interval**
   Optionally, you can set the interval for multiplexing between different modes using the `setMultiplexInterval` function. This interval is specified in milliseconds and determines how frequently the display switches between active modes.

    ```cpp
    void setup() {
        onboard.begin();
        int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
        onboard.setModesMultiplex(activeModes, 3);
        onboard.setMultiplexInterval(100); // Set multiplex interval to 100 milliseconds
    }
    ```

4. **Update Multiplex in the Loop**
   Ensure that you call the `updateMultiplex` function inside your `loop()` function. This function handles the actual switching between the modes based on the specified interval.

    ```cpp
    void loop() {
        onboard.updateMultiplex();
        // Add any other code that needs to run continuously
    }
    ```

5. **Updating Display Values**
   Update the values for the HEX display, RGB LED, and LED stripe in your `loop()` function or based on specific events. These values will be shown according to the active multiplex mode.

    ```cpp
    void loop() {
        unsigned long currentTime = millis();

        if (currentTime - lastHexUpdateTime >= HEX_UPDATE_INTERVAL) {
            lastHexUpdateTime = currentTime;
            hexNumber++;
            if (hexNumber > 15) hexNumber = -15; // Reset hexNumber after it exceeds the range
        }

        if (currentTime - lastRgbUpdateTime >= RGB_UPDATE_INTERVAL) {
            lastRgbUpdateTime = currentTime;
            red += 5;
            green += 3;
            blue += 7;
            if (red > 255) red = 0;
            if (green > 255) green = 0;
            if (blue > 255) blue = 0;
        }

        if (currentTime - lastStripeUpdateTime >= STRIPE_UPDATE_INTERVAL) {
            lastStripeUpdateTime = currentTime;
            ledStripeValue++;
            if (ledStripeValue > 1023) ledStripeValue = 0; // Reset ledStripeValue after it exceeds the range
        }

        onboard.updateMultiplex();
    }
    ```

### Example Code

Below is a complete example that demonstrates how to set up and use multiplex mode:

```cpp
#include <HTL_onboard.h>

#define MODE_HEX 0
#define MODE_STRIPE 1
#define MODE_RGB 2

#define HEX_UPDATE_INTERVAL 1000 // Interval for updating HEX display in milliseconds
#define RGB_UPDATE_INTERVAL 50   // Interval for updating RGB LED in milliseconds
#define STRIPE_UPDATE_INTERVAL 200 // Interval for updating LED stripe in milliseconds

HTL_onboard onboard;

unsigned long lastHexUpdateTime = 0;
unsigned long lastRgbUpdateTime = 0;
unsigned long lastStripeUpdateTime = 0;

int hexNumber = 0; // Variable to hold the current number for HEX display
uint8_t red = 0, green = 0, blue = 0; // Variables for RGB LED
int ledStripeValue = 0; // Variable for LED stripe

void setup() {
    onboard.begin();
    int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
    onboard.setModesMultiplex(activeModes, 3); // Activate HEX, RGB, and LED stripe modes
    onboard.setMultiplexInterval(100); // Set multiplex interval to 100 milliseconds
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastHexUpdateTime >= HEX_UPDATE_INTERVAL) {
        lastHexUpdateTime = currentTime;
        hexNumber++;
        if (hexNumber > 15) hexNumber = -15; // Reset hexNumber after it exceeds the range
    }

    if (currentTime - lastRgbUpdateTime >= RGB_UPDATE_INTERVAL) {
        lastRgbUpdateTime = currentTime;
        red += 5;
        green += 3;
        blue += 7;
        if (red > 255) red = 0;
        if (green > 255) green = 0;
        if (blue > 255) blue = 0;
    }

    if (currentTime - lastStripeUpdateTime >= STRIPE_UPDATE_INTERVAL) {
        lastStripeUpdateTime = currentTime;
        ledStripeValue++;
        if (ledStripeValue > 1023) ledStripeValue = 0; // Reset ledStripeValue after it exceeds the range
    }

    onboard.updateMultiplex();
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

- `void updateMultiplex()`
  - Updates all displays. Call this function in loop().

- `void setModesMultiplex(const int modes[], int size)`
  - Sets the modes which are used to display in multiplex operation.
  - `modes`: Array of modes that are displayed in Multiplex mode (0 for HEX, 1 for LED stripe, 2 for RGB).
  - `size`: Size of the modes array.

- `void setMultiplexInterval(int multiplexInterval)`
  - Sets the interval for multiplexing between different display modes.
  - This function sets the interval, in milliseconds, for how frequently the system cycles through the different active display modes (HEX, LED stripe, RGB).
  - The provided interval must be non-negative.
  - `multiplexInterval`: The time interval in milliseconds for multiplexing. Must be a non-negative integer.

## Author
Tobias Weich, 2024
