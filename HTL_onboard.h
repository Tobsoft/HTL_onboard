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

#ifndef HTL_ONBOARD_H
#define HTL_ONBOARD_H

#include <Arduino.h>

/**
 * @brief Library for controlling onboard hardware components including HEX display, LED stripe, and RGB LED.
 * 
 * This library provides functions to control various onboard hardware components of the HTL Uno,
 * including a HEX display, LED stripe, and RGB LED. It allows for displaying hexadecimal and integer
 * values on the HEX display, controlling individual LEDs on the LED stripe, setting colors on the RGB LED,
 * reading switch states, and reading the value of a potentiometer.
 * 
 * 
 * Tobias Weich 2024
 */
class HTL_onboard {
public:
    HTL_onboard();

    /**
     * @brief Initializes the HTL_onboard library.
     * 
     * Sets up pin modes for all necessary pins.
     */
    void begin();

    /**
     * @brief Writes a hexadecimal number to the HEX display.
     * 
     * @param hexNumber The hexadecimal number to display (-15 to 15).
     */
    void writeHex(int8_t hexNumber);

    /**
     * @brief Writes an integer to the HEX display.
     * 
     * @param intNumber The integer number to display (-19 to 19).
     */
    void writeInt(int8_t intNumber);

    /**
     * @brief Writes a binary value to the LED stripe.
     * 
     * @param binValue The binary value to display (0 to 1023).
     */
    void writeBinary(int binValue);

    /**
     * @brief Sets a specific LED on the LED stripe.
     * 
     * @param pin The pin number of the LED to set (0 to 9).
     */
    void setLED(int pin);

    /**
     * @brief Clears a specific LED on the LED stripe.
     * 
     * This function turns off the specified LED on the LED stripe by setting its corresponding pin to HIGH.
     * 
     * @param pin The pin number of the LED to clear (0 to 9).
     */
    void clearLED(int pin);

    /**
     * @brief Clears all LEDs on the LED stripe (turns them off).
     */
    void clearStripe();

    /**
     * @brief Sets the RGB LED to the specified color.
     * 
     * @param red The red intensity (0 to 255).
     * @param green The green intensity (0 to 255).
     * @param blue The blue intensity (0 to 255).
     */
    void setRGB(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * @brief Reads the state of the switches.
     * 
     * @return int Returns 2 if switch 2 is pressed, 3 if switch 3 is pressed, 1 if both switches are pressed, and 0 if no switch is pressed.
     */
    int readSwitchState();

    /**
     * @brief Reads the potentiometer value.
     * 
     * @return int The analog value from the potentiometer (0-1023).
     */
    int readPot();

    /**
     * @brief Sets the mode of the HTL_onboard.
     * 
     * @param mode The mode to set (0 for HEX, 1 for LED stripe, 2 for RGB).
     * @param state The state to set the mode to (true for active, false for inactive).
     */
    void setMode(int mode, bool state);

    /**
     * @brief Configures the switch thresholds.
     * 
     * @param switch1Threshold Threshold for switch 1.
     * @param switch2Threshold Threshold for switch 2.
     * @param switch12Min Minimum threshold for both switches pressed.
     * @param switch12Max Maximum threshold for both switches pressed.
     */
    void cfgSwitches(int switch1Threshold, int switch2Threshold, int switch12Min, int switch12Max);

private:
    /**
     * @brief Sets the pins of the LED-Stripe based on the provided value.
     * 
     * @param value The value to set the pins to.
     */
    void setPins(uint8_t value);

    const uint8_t pinMapping[10] = {0, 1, 2, 3, 4, 5, 6, 8, 7, 9}; // abcdefgNhi
    const uint8_t pinMappingStripe[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const uint8_t selectPins[3] = {10, 11, 12}; // HEX-Panel, LED-Stripe, RGB-LED

    int switch1Threshold = 400;
    int switch2Threshold = 690;
    int switch12Min = 500;
    int switch12Max = 520;
};

#endif