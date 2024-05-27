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

## Multiplex

The HTL_onboard library supports multiplexing, allowing you to cycle through different display modes (HEX display, LED stripe, RGB LED) at regular intervals. This section provides details on how to use the multiplexing methods provided by the library.

### Setting Up Multiplexing

To use multiplexing, follow these steps:

1. **Initialize the Library**: Begin by initializing the HTL_onboard library using the `begin()` method.

    ```cpp
    onboard.begin();
    ```

2. **Define Active Modes**: Define an array of active modes that you want to cycle through during multiplexing. Each mode is represented by an integer value: 0 for HEX display, 1 for LED stripe, and 2 for RGB LED. You can also use the predefined Macros MODE_HEX, MODE_RGB and MODE_STRIPE.

    ```cpp
    int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
    ```

3. **Set Multiplexing Modes**: Use the `setModesMultiplex()` method to set the active modes for multiplexing.

    ```cpp
    onboard.setModesMultiplex(activeModes, 3);
    ```

4. **Set Multiplex Interval**: Specify the interval, in milliseconds, for how frequently the system cycles through the different active display modes using the `setMultiplexInterval()` method. The provided interval must be a non-negative integer.

    ```cpp
    onboard.setMultiplexInterval(5); // Set interval to 5ms
    ```

### Updating Multiplexing

After setting up multiplexing, you need to regularly call the `updateMultiplex()` method within the `loop()` function to cycle through the active display modes. This ensures smooth transition between different modes.

```cpp
void loop() {
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

- `void cfgSwitches(int switch1Threshold, int switchNoneThreshold, int switch12Threshold)`
  - Configures the switch thresholds used for checking which switch was pressed.
  - `switch1Threshold`: Threshold for switch 1.
  - `switchNoneThreshold`: Threshold for no switch pressed.
  - `switch12Threshold`: Threshold for both switches pressed.

- `void updateMultiplex()`
  - Updates all displays. Call this function in loop().

- `void setModesMultiplex(const int modes[], int size)`
  - Sets the modes which are used to display in multiplex operation.
  - `modes`: Array of modes that are displayed in Multiplex mode. (0 for HEX, 1 for LED stripe, 2 for RGB).
  - `size`: Size of the modes array.

- `void setMultiplexInterval(int multiplexInterval)`
  - Sets the interval for multiplexing between different display modes.
  - This function sets the interval, in milliseconds, for how frequently the system cycles through the different active display modes (HEX, LED stripe, RGB).
  - The provided interval must be non-negative.
  - `multiplexInterval`: The time interval in milliseconds for multiplexing. Must be a non-negative integer.

- `void setHexMode(int mode)`
  - Sets the display mode of the HEX display.
  - `mode`: The mode to set (0 for HEX, 1 for Decimal).

- `int getHexMode()`
  - Gets the current display mode of the HEX display.
  - Returns the current display mode (0 for HEX, 1 for Decimal).

- `void setHexNumber(int number)`
  - Sets the number to be displayed on the HEX display.
  - `number`: The number to display (-15 to 15 in HEX mode, -19 to 19 in Decimal mode).

- `int getHexNumber()`
  - Gets the number currently displayed on the HEX display.
  - Returns the number displayed on the HEX display.

- `void setRed(uint8_t r)`
  - Sets the intensity of the red component of the RGB LED.
  - `r`: The intensity of the red component (0 to 255).

- `void setGreen(uint8_t g)`
  - Sets the intensity of the green component of the RGB LED.
  - `g`: The intensity of the green component (0 to 255).

- `void setBlue(uint8_t b)`
  - Sets the intensity of the blue component of the RGB LED.
  - `b`: The intensity of the blue component (0 to 255).

- `uint8_t getRed()`
  - Gets the intensity of the red component of the RGB LED.
  - Returns the intensity of the red component (0 to 255).

- `uint8_t getGreen()`
  - Gets the intensity of the green component of the RGB LED.
  - Returns the intensity of the green component (0 to 255).

- `uint8_t getBlue()`
  - Gets the intensity of the blue component of the RGB LED.
  - Returns the intensity of the blue component (0 to 255).

- `void setLedStripeValue(int value)`
  - Sets the value of the LED stripe.
  - `value`: The value to set (0 to 1023).

- `int getLedStripeValue()`
  - Gets the current value of the LED stripe.
  - Returns the current value of the LED stripe (0 to 1023).

## Author
Tobias Weich, 2024
