# HTL_onboard Library
The HTL_onboard library provides functions to control the onboard hardware components of the HTL Uno development board, including the HEX display, LED stripe, RGB LED, switches, and potentiometer.

[German Version](README_GERMAN.md)

## Installation
### Installation via Arduino Library Manager
1. Open the Arduino IDE.
2. Navigate to **Sketch > Include Library > Manage Libraries...** This will open the Library Manager.
3. In the search bar, type "HTL_onboard" and press Enter.
4. From the search results, locate the "HTL_onboard" library.
5. Click on the "Install" button to install the library.
6. Once installation is complete, close the Library Manager.
7. You can now include the HTL_onboard library in your sketches by typing "#include <HTL_onboard.h>."

### Installation via .zip File
1. Download the HTL_onboard library (.zip) from the [HTL_onboard github repository](https://github.com/Tobsoft/HTL_onboard).
2. Add the library to your Arduino IDE by navigating to Sketch > Include Library > Add .ZIP Library... and selecting the downloaded ZIP file.

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

*For additional examples go to FIle > Examples > Examples from Custom Libraries > HTL_onboard in the Arduino IDE*

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

**Note:** In order to change values in multiplex mode, it is recommended to **use the setters** provided by the library, e.g., use setHexNumber() instead of writeHex(). This ensures that the values are correctly updated and displayed within the multiplexing framework.
```cpp
// Correct way to set HEX number in multiplex mode
onboard.setHexNumber(10);

// Correct way to set LED stripe value in multiplex mode
onboard.setLedStripeValue(512);

// Correct way to set RGB values in multiplex mode
onboard.setRed(255);
onboard.setGreen(255);
onboard.setBlue(255);
```


## Documentation

### HTL_onboard Class

The `HTL_onboard` class provides control over various onboard hardware components of the HTL Uno, including a HEX display, LED stripe, and RGB LED. It offers methods to display values, control LEDs, set colors, read switches and potentiometer values, and manage display modes. The class supports Multiplex operation.

#### Public Methods

- `HTL_onboard()`
  - Constructor for initializing the HTL_onboard library.

- `void begin()`
  - Initializes the library and sets up pin modes for all necessary pins.

- `void writeHex(int8_t hexNumber)`
  - Writes a hexadecimal number (-15 to 15) to the HEX display.

- `void writeInt(int8_t intNumber)`
  - Writes an integer (-19 to 19) to the HEX display.

- `void writeChar(char c)`
  - Displays a character on the 7-segment display.

- `void writeBinary(int binValue)`
  - Writes a binary value (0 to 1023) to the LED stripe.

- `void setLED(int pin)`
  - Sets a specific LED (0 to 9) on the LED stripe.

- `void clearLED(int pin)`
  - Clears a specific LED (0 to 9) on the LED stripe.

- `void clearStripe()`
  - Clears all LEDs on the LED stripe.

- `void setRGB(uint8_t red, uint8_t green, uint8_t blue)`
  - Sets the RGB LED to the specified color (0 to 255 for each component).

- `int readSwitchState()`
  - Reads the state of the switches and returns:
    - `2` if switch 2 is pressed,
    - `3` if switch 3 is pressed,
    - `1` if both switches are pressed,
    - `0` if no switch is pressed.

- `int readPot()`
  - Reads the value of the potentiometer (0-1023).

- `void setMode(int mode, bool state)`
  - Sets the mode of the HTL_onboard (0 for HEX, 1 for LED stripe, 2 for RGB).

- `void cfgSwitches(int switch1Threshold, int switchNoneThreshold, int switch12Threshold)`
  - Configures thresholds for switch states.

- `void updateMultiplex()`
  - Updates all displays. Should be called in the `loop()` function.

- `void setModesMultiplex(const int modes[], int size)`
  - Sets the modes used in multiplex operation (0 for HEX, 1 for LED stripe, 2 for RGB).

- `void setMultiplexInterval(int multiplexInterval)`
  - Sets the interval (in milliseconds) for multiplexing between different display modes.

- `void setHexMode(int mode)`
  - Sets the display mode of the HEX display (0 for HEX, 1 for Decimal, 2 for Character).

- `int getHexMode()`
  - Retrieves the current display mode of the HEX display.

- `void setHexNumber(int number)`
  - Sets the number to be displayed on the HEX display (-15 to 15 in HEX mode, -19 to 19 in Decimal mode).

- `int getHexNumber()`
  - Retrieves the number/character currently displayed on the HEX display.

- `void setChar(char c)`
  - Sets the character to be displayed on the HEX display.

- `void setString(String str)`
  - Sets the string to be displayed on the HEX display.

- `String getString()`
  - Retrieves the string currently displayed on the HEX display.

- `void setRed(uint8_t r)`
  - Sets the intensity of the red component of the RGB LED (0 to 255).

- `void setGreen(uint8_t g)`
  - Sets the intensity of the green component of the RGB LED (0 to 255).

- `void setBlue(uint8_t b)`
  - Sets the intensity of the blue component of the RGB LED (0 to 255).

- `uint8_t getRed()`
  - Retrieves the intensity of the red component of the RGB LED.

- `uint8_t getGreen()`
  - Retrieves the intensity of the green component of the RGB LED.

- `uint8_t getBlue()`
  - Retrieves the intensity of the blue component of the RGB LED.

- `void setStringDelay(int stringDelay)`
  - Sets the delay (in milliseconds) for displaying each character in string display mode.

- `int getStringDelay()`
  - Retrieves the current delay (in milliseconds) for displaying each character in string display mode.

- `void setLedStripeValue(int value)`
  - Sets the value (0 to 1023) of the LED stripe.

- `int getLedStripeValue()`
  - Retrieves the current value (0 to 1023) of the LED stripe.

## Author
Tobias Weich, 2024