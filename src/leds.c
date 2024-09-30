/**
 * @file leds.c
 * @author Marco Rolon Radcenco
 * @brief LED Port Control Source File
 *
 * This file provides functions for controlling LEDs on a specific port. It includes
 * functions to initialize the port, turn LEDs on or off, and check their status.
 */

#include "leds.h"
#include <stddef.h>

/**
 * @brief Least significant bit used to represent the first LED.
 */
#define LEDS_LSB 0x0001

/**
 * @brief The index of the last LED in the system.
 */
#define LEDS_LAST_LED 16

/**
 * @brief The index of the first LED in the system.
 */
#define LEDS_FIRST_LED 1

/**
 * @brief Offset to correctly map LED numbers to bitmask positions.
 */
#define LEDS_LED_OFFSET 1

/**
 * @brief Mask representing all LEDs turned off.
 */
#define LEDS_ALL_OFF 0x0000

/**
 * @brief Mask representing all LEDs turned on.
 */
#define LEDS_ALL_ON 0xFFFF

/**
 * @brief Pointer to the memory address that controls the LED port.
 *
 * This static pointer stores the address of the memory location
 * used to control the state of the LEDs. It is initialized in
 * the LEDs_Create function.
 */
static uint16_t * _leds_port;

/**
 * @brief Converts an LED index to a bitmask.
 *
 * This static function shifts the least significant bit (LSB) to the position
 * corresponding to the given LED index.
 *
 * @param led Index of the LED.
 * @return Bitmask corresponding to the LED.
 */
static uint16_t indexToMask(int led) {
    return LEDS_LSB << (led - LEDS_LED_OFFSET);
}

/**
 * @brief Checks if the LED number is within the valid range.
 *
 * This static function ensures that the provided LED number falls within the
 * valid range of LEDS_FIRST_LED to LEDS_LAST_LED.
 *
 * @param led Index of the LED to check.
 * @return true if the LED is within range, false otherwise.
 */
static bool isValidIndex(int led) {
    return ((LEDS_LAST_LED >= led) && (LEDS_FIRST_LED <= led));
}

bool LEDs_Create(uint16_t * port_address) {
    if (NULL == port_address) {
        return false;
    } else {
        _leds_port = port_address;
        LEDs_SetAllOff();
        return true;
    }
}

bool LEDs_SetOff(int led) {
    if (isValidIndex(led)) {
        *_leds_port &= ~indexToMask(led);
        return true;
    } else {
        return false;
    }
}

void LEDs_SetAllOff(void) {
    *_leds_port = LEDS_ALL_OFF;
}

bool LEDs_SetOn(int led) {
    if (isValidIndex(led)) {
        *_leds_port |= indexToMask(led);
        return true;
    } else {
        return false;
    }
}

void LEDs_SetAllOn(void) {
    *_leds_port = LEDS_ALL_ON;
}

bool LEDs_IsOn(int led) {
    return (indexToMask(led) == (*_leds_port & indexToMask(led)));
}
