/*
   Copyright 2024 Tobias Weich
*/

/*
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "HTL_onboard.h"

// Segment mapping for hexadecimal digits (0-9, A-F)
// Bit order: abcdefg (g is the LSB)
const uint8_t segmentMap[16] = {
    0b01111110,  // 0
    0b00110000,  // 1
    0b01101101,  // 2
    0b01111001,  // 3
    0b00110011,  // 4
    0b01011011,  // 5
    0b01011111,  // 6
    0b01110000,  // 7
    0b01111111,  // 8
    0b01111011,  // 9
    0b01110111,  // A
    0b00011111,  // b
    0b01001110,  // C
    0b00111101,  // d
    0b01001111,  // E
    0b01000111   // F
};

HTL_onboard::HTL_onboard() {}

void HTL_onboard::begin() {
    // Initialize all pins as output
    for (int i = 0; i < 10; i++) {
        pinMode(pinMapping[i], OUTPUT);
    }

    for (int i = 0; i < 3; i++) {
        pinMode(selectPins[i], OUTPUT);
    }

    pinMode(A0, INPUT);
    pinMode(A1, INPUT_PULLUP);

    for (int i = 0; i < 3; i++) {
        setMode(i, false);
    }
}

void HTL_onboard::writeHex(int8_t hexNumber) {
    setMode(MODE_HEX, true);
    setHexMode(HEX_MODE_HEX);

    if (hexNumber < -15 || hexNumber > 15) {
        return;  // Out of range
    }

    this->hexNumber = hexNumber;

    if (hexNumber < 0) {
        digitalWrite(pinMapping[7], LOW);
        hexNumber = -hexNumber;
    } else {
        digitalWrite(pinMapping[7], HIGH);
    }

    digitalWrite(pinMapping[8], HIGH);
    digitalWrite(pinMapping[9], HIGH);

    uint8_t value = segmentMap[hexNumber];
    setPins(value);
}

void HTL_onboard::writeInt(int8_t intNumber) {
    setMode(MODE_HEX, true);
    setHexMode(HEX_MODE_DEC);

    if (intNumber < -19 || intNumber > 19) {
        return;  // Out of range
    }

    hexNumber = intNumber;

    if (intNumber < 0) {
        digitalWrite(pinMapping[7], LOW);
        intNumber = -intNumber;
    } else {
        digitalWrite(pinMapping[7], HIGH);
    }

    if (intNumber > 9) {
        digitalWrite(pinMapping[8], LOW);
        digitalWrite(pinMapping[9], LOW);
        intNumber -= 10;
    } else {
        digitalWrite(pinMapping[8], HIGH);
        digitalWrite(pinMapping[9], HIGH);
    }

    uint8_t value = segmentMap[intNumber];
    setPins(value);
}

void HTL_onboard::setPins(uint8_t value) {
    for (int i = 6; i >= 0; i--) {
        digitalWrite(pinMapping[i], (value & (1 << (6 - i))) ? LOW : HIGH);  // Active low logic
    }
}

void HTL_onboard::setMode(int mode, bool state) {
    // Set Pins to Output
    for (int i = 0; i < 10; i++) {
        pinMode(pinMapping[i], OUTPUT);
        // Set Pins to Off (HIGH)
        digitalWrite(pinMapping[i], HIGH);
    }

    // Ensure the mode is within the bounds of selectPins array
    if (mode >= 0 && mode < (sizeof(selectPins) / sizeof(selectPins[0]))) {
        digitalWrite(selectPins[mode], state ? LOW : HIGH);  // Active low logic
    }
}

void HTL_onboard::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
    setMode(MODE_RGB, true);

    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);
    
    this->red = red;
    this->green = green;
    this->blue = blue;

    // Set the RGB LED pins to the specified intensity
    analogWrite(5, 255 - red);
    analogWrite(6, 255 - green);
    analogWrite(9, 255 - blue);
}

void HTL_onboard::writeBinary(int binValue) {
    setMode(MODE_STRIPE, true);

    // Ensure the binValue is within the range of 0 to 1023 (10 bits)
    if (binValue < 0 || binValue > 1023) {
        return; // Out of range
    }

    ledStripeValue = binValue;

    // Set each LED according to the corresponding bit in binValue
    for (int i = 0; i < 10; i++) {
        digitalWrite(pinMappingStripe[i], (binValue & (1 << i)) ? LOW : HIGH); // Active low logic
    }
}

void HTL_onboard::setLED(int pin) {
    setMode(MODE_STRIPE, true);

    // Ensure the pin number is within the range of 0 to 9
    if (pin < 0 || pin > 9) {
        return; // Out of range
    }

    // Set the specified LED pin to LOW (ON)
    digitalWrite(pinMappingStripe[pin], LOW);

    // Update ledStripeValue to reflect the change
    ledStripeValue |= (1 << pin);
}

void HTL_onboard::clearLED(int pin) {
    setMode(MODE_STRIPE, true);

    // Ensure the pin number is within the range of 0 to 9
    if (pin < 0 || pin > 9) {
        return; // Out of range
    }

    // Set the specified LED pin to HIGH (OFF)
    digitalWrite(pinMappingStripe[pin], HIGH);

    // Update ledStripeValue to reflect the change
    ledStripeValue &= ~(1 << pin);
}

void HTL_onboard::clearStripe() {
    setMode(MODE_STRIPE, true);

    // Turn off all LEDs in the LED-Stripe (set them to HIGH)
    for (int i = 0; i < 10; i++) {
        digitalWrite(pinMappingStripe[i], HIGH);
    }
}

int HTL_onboard::readSwitchState() {
    // Read the analog voltage on pin A1
    int analogValue = analogRead(A1);

    // Check the voltage level and determine the switch state
    if (analogValue > switchNoneThreshold) {
        return 0; // Both switches are inactive
    } else if (analogValue > switch1Threshold) {
        return 2; // Switch 2 is active
    } else if (analogValue > switch12Threshold) {
        return 1; // Both switches are active
    } else {
        return 3; // Switch 3 is active
    }
}

int HTL_onboard::readPot() {
    return analogRead(A0);
}

void HTL_onboard::cfgSwitches(int switch1Threshold, int switchNoneThreshold, int switch12Threshold) {
    this->switch1Threshold = switch1Threshold;
    this->switchNoneThreshold = switchNoneThreshold;
    this->switch12Threshold = switch12Threshold;
}

void HTL_onboard::updateMultiplex() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastMultiplexTime >= multiplexInterval) {
        lastMultiplexTime = currentTime;

        // Check if any mode is active
        bool flag = false;
        for (int i = 0; i < 3; i++) {
            if (modesActive[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return;
        }

        // Cycle through active display modes
        int nextMode = currentMode;
        do {
            nextMode += 1;
	    if (nextMode > 2) {
		nextMode = 0;
	    }
        } while (!modesActive[nextMode]);

        // Turn off all displays before switching
        setMode(MODE_HEX, false);
        setMode(MODE_STRIPE, false);
        setMode(MODE_RGB, false);

        switch (nextMode) {
            case MODE_HEX:
                HEX_mode == 0 ? writeHex(hexNumber) : writeInt(hexNumber); // Update with current hex number
                break;
            case MODE_RGB:
                setRGB(red, green, blue); // Update with current RGB values
                delay(RGB_DELAY);
                break;
            case MODE_STRIPE:
                writeBinary(ledStripeValue); // Update with current LED stripe value
                break;
        }

        // Update the currentMode to the next active mode
        currentMode = nextMode;
    }
}

void HTL_onboard::setModesMultiplex(const int modes[], int size) {
    // Reset all modes to inactive
    for (int i = 0; i < 3; i++) {
        modesActive[i] = false;
    }
    
    // Set the specified modes to active
    for (int i = 0; i < size; i++) {
        int mode = modes[i];
        if (mode >= 0 && mode < 3) {
            modesActive[mode] = true;
        }
    }
}

void HTL_onboard::setMultiplexInterval(int multiplexInterval) {
    if (multiplexInterval >= 0) {
	this -> multiplexInterval = multiplexInterval;
    }
}

void HTL_onboard::setHexMode(int mode) {
    if (mode == 0 || mode == 1) {
        HEX_mode = mode;
    }
}

int HTL_onboard::getHexMode() {
    return HEX_mode;
}

void HTL_onboard::setHexNumber(int number) {
    if (HEX_mode == 0) {
        hexNumber = constrain(number, -15, 15);
    } else {
        hexNumber = constrain(number, -19, 19);
    }
}

int HTL_onboard::getHexNumber() {
    return hexNumber;
}

void HTL_onboard::setRed(uint8_t r) {
    red = constrain(r, 0, 255);
}

void HTL_onboard::setGreen(uint8_t g) {
    green = constrain(g, 0, 255);
}

void HTL_onboard::setBlue(uint8_t b) {
    blue = constrain(b, 0, 255);
}

uint8_t HTL_onboard::getRed() {
    return red;
}

uint8_t HTL_onboard::getGreen() {
    return green;
}

uint8_t HTL_onboard::getBlue() {
    return blue;
}

void HTL_onboard::setLedStripeValue(int value) {
    ledStripeValue = constrain(value, 0, 1023);
}

int HTL_onboard::getLedStripeValue() {
    return ledStripeValue;
}