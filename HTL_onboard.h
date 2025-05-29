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
#include <string.h>

#define MODE_HEX 0
#define MODE_STRIPE 1
#define MODE_RGB 2

#define HEX_MODE_HEX 0
#define HEX_MODE_DEC 1
#define HEX_MODE_CHAR 2
#define HEX_MODE_STRING 3

#define STRIPE_MODE_BIN 0
#define STRIPE_MODE_PROG 1

#define RGB_DELAY 1 // How long to keep the RGB Led on in milliseconds
                    // WARNING: SETTING THIS TO A HIGH VALUE MAY DECREASE MULTIPLEXING FREQUENCY AND CAUSE FLICKERING IN OTHER MODES!
                    // Maximum suggested value ~30

// Define Pin Names for Breakout Pins(B)
// B1 is Pin 1 of X17
/*  
    B1 B2 B3 B4 B5 B6
    .  .  .  .  .  . 
   |- X17 -||- X16 -|
    1  2  3  1  2  3
*/

#define B1 GND
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define B6 6

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
     * @param hexNumber The hexadecimal number to display (-1F to 1F).
     */
    void writeHex(int8_t hexNumber);

    /**
     * @brief Writes an integer to the HEX display.
     * 
     * @param intNumber The integer number to display (-19 to 19).
     */
    void writeInt(int8_t intNumber);

    /**
    * @brief Display a character on the 7-segment display.
    * 
    * Displaying characters is supported in Multiplex mode
    * 
    * This function attempts to display the provided character on the
    * 7-segment display. If the character is not directly supported,
    * it will attempt to display the uppercase or lowercase equivalent.
    * If the character is still unsupported, it defaults to displaying '0'.
    * 
    * @param c The character to display.
    */
    void writeChar(char c);

    /**
     * @brief Writes a binary value to the LED stripe.
     * 
     * @param binValue The binary value to display (0 to 1023).
     */
    void writeBinary(int binValue);

    /**
     * @brief Writes a value to the LED stripe in Progress Bar form.
     * 
     * @param progressValue The progress value to display (0 to 10).
     */
    void writeProgress(int progressValue);

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
     * @param switchNoneThreshold Threshold for no switch pressed.
     * @param switch12Threshold Threshold for both switches pressed.
     */
    void cfgSwitches(int switch1Threshold, int switchNoneThreshold, int switch12Threshold);

   /**
    * @brief Updates all displays. Call this function in loop()
    */
    void updateMultiplex();

   /**
    * @brief Sets the modes which are used to display in multiplex operation.
    *
    * @param modes array of modes that are displayed in Multiplex mode. (0 for HEX, 1 for LED stripe, 2 for RGB)
    */
    void setModesMultiplex(const int modes[], int size);
    
    /**
    * @brief Sets the interval for multiplexing between different display modes.
    *
    * This function sets the interval, in milliseconds, for how frequently the
    * system cycles through the different active display modes (HEX, LED stripe, RGB).
    * The provided interval must be non-negative.
    *
    * @param multiplexInterval The time interval in milliseconds for multiplexing.
    *                          Must be a non-negative integer.
    */
    void setMultiplexInterval(int multiplexInterval);

    /**
     * @brief Sets the display mode of the HEX display.
     * 
     * @param mode The mode to set (0 for HEX, 1 for Decimal, 2 for Character).
     */
    void setHexMode(int mode);

    /**
     * @brief Gets the current display mode of the HEX display.
     * 
     * @return int The current display mode (0 for HEX, 1 for Decimal, 2 for Character, 3 for String).
     */
    int getHexMode();

    /**
     * @brief Sets the number to be displayed on the HEX display.
     * 
     * @param number The number to display (-15 to 15 in HEX mode, -19 to 19 in Decimal mode).
     */
    void setHexNumber(int number);

    /**
     * @brief Gets the number/character currently displayed on the HEX display.
     * 
     * @return int The number/character displayed on the HEX display as int.
     */
    int getHexNumber();

    /**
     * @brief Sets the character to be displayed on the HEX display.
     * 
     * @param c The character to display (ASCII).
     */
    void setChar(char c);

    /**
     * @brief Sets the string to be displayed on the HEX display.
     * 
     * The string gets displayed character by character, with each character being displayed for strDelay (ms).
     * Displaying strings is only supported for Multiplex mode, for Hex_mode only use setChar or only activate HEX mode
     * 
     * @param str The string to display (ASCII).
     */
    void setString(String str);

    /**
     * @brief Gets the string to be displayed on the HEX display.
     * 
     * @return String The string being displayed.
     */
    String getString();

    /**
     * @brief Sets the display mode of the LED Stripe.
     * 
     * @param mode The mode to set (0 for Binary, 1 for Progress).
     */
    void setStripeMode(int mode);

    /**
     * @brief Gets the current display mode of the LED Stripe.
     * 
     * @return int The current display mode (0 for Binary, 1 for Progress).
     */
    int getStripeMode();

    /**
    *   @brief Sets the RGB Values used in Multiplex Mode
    * 
    *   @param red The red intensity (0 to 255).
    *   @param green The green intensity (0 to 255).
    *   @param blue The blue intensity (0 to 255).
    *
     */
    void setRGB_Multiplex(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * @brief Sets the intensity of the red component of the RGB LED.
     * 
     * @param r The intensity of the red component (0 to 255).
     */
    void setRed(uint8_t r);

    /**
     * @brief Sets the intensity of the green component of the RGB LED.
     * 
     * @param g The intensity of the green component (0 to 255).
     */
    void setGreen(uint8_t g);

    /**
     * @brief Sets the intensity of the blue component of the RGB LED.
     * 
     * @param b The intensity of the blue component (0 to 255).
     */
    void setBlue(uint8_t b);

    /**
     * @brief Gets the intensity of the red component of the RGB LED.
     * 
     * @return uint8_t The intensity of the red component (0 to 255).
     */
    uint8_t getRed();

    /**
     * @brief Gets the intensity of the green component of the RGB LED.
     * 
     * @return uint8_t The intensity of the green component (0 to 255).
     */
    uint8_t getGreen();

    /**
     * @brief Gets the intensity of the blue component of the RGB LED.
     * 
     * @return uint8_t The intensity of the blue component (0 to 255).
     */
    uint8_t getBlue();

    /**
     * @brief Sets the delay of how long to display a character in string display mode.
     * 
     * @param ms The delay in ms.
     */
    void setStringDelay(int stringDelay);

    /**
     * @brief Gets the delay of how long to display a character in string display mode.
     * 
     * @return int The delay in ms.
     */
    int getStringDelay();

    /**
     * @brief Sets the value of the LED stripe.
     * 
     * @param value The value to set (0 to 1023).
     */
    void setLedStripeValue(int value);

    /**
     * @brief Gets the current value of the LED stripe.
     * 
     * @return int The current value of the LED stripe (0 to 1023).
     */
    int getLedStripeValue();

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

    // Note that switch 1 is S2 and switch 2 is S3
    int switch1Threshold = 700;
    int switchNoneThreshold = 900;
    int switch12Threshold = 500;

    unsigned long lastMultiplexTime = 0;
    int currentMode = 0; // Start with HEX display
    bool modesActive[3] = {false, false, false}; // Track active modes
    int multiplexInterval = 1;

    int HEX_mode = 0; // 0: display as HEX, 1: display as Decimal, 2: display as character, 3: display as String
    int hexNumber = 0; // Variable to hold the current number for HEX display
    int stripeMode = 0; //0: display as binary, 1: display as progress
    int ledStripeValue = 0; // Variable for LED stripe
    String str = "";
    int strDelay = 500;
    unsigned long lastStringUpdateTime = 0;
    int strInx = 0;
    uint8_t red = 0, green = 0, blue = 0; // Variables for RGB LED
};

#endif