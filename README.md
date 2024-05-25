# HTL_onboard Library
The HTL_onboard library provides functions to control the onboard hardware components of the HTL Uno development board, including the HEX display, LED stripe, RGB LED, switches, and potentiometer.

## Installation
Download the HTL_onboard library.
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
### Reading Potentiometer Value
```cpp
#include <HTL_onboard.h>

HTL_onboard onboard;

void setup() {
    Serial.begin(9600);
    onboard.begin();
}

void loop() {
    int potValue = onboard.readPot();
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);
    delay(1000);
}
```

### Controlling LED Stripe
```cpp
#include <HTL_onboard.h>

HTL_onboard onboard;

void setup() {
    onboard.begin();
}

void loop() {
    // Turn on LED at pin 3
    onboard.setLED(3);
    delay(1000);
    
    // Turn off LED at pin 3
    onboard.clearLED(3);
    delay(1000);
}
```

## Documentation
For detailed documentation of available functions and their usage, please refer to the HTL_onboard.h header file.

## Author
Tobias Weich, 2024
