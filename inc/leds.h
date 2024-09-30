/**
 * @file leds.h
 * @author Marco Rolon Radcenco
 * @brief LED Port Control Header File
 *
 * This file provides functions for controlling LEDs on a specific port. It includes
 * functions to initialize the port, turn LEDs on or off, and check their status.
 */

#ifndef LEDS_H
#define LEDS_H

#include "stdbool.h"
#include "stdint.h"

/**
 * @brief Initializes the LED port and turns all LEDs off.
 *
 * This function initializes the port for LED control and ensures that all LEDs are turned off
 * initially.
 *
 * @param port Pointer to the LED port.
 * @return true if initialization was successful, false otherwise.
 */
bool LEDs_Create(uint16_t * port);

/**
 * @brief Turns off the specified LED.
 *
 * This function turns off a specific LED by its index.
 *
 * @param led Index of the LED to turn off.
 * @return true if the operation was successful, false otherwise.
 */
bool LEDs_SetOff(int led);

/**
 * @brief Turns off all LEDs.
 *
 * This function turns off all the LEDs connected to the port.
 */
void LEDs_SetAllOff(void);

/**
 * @brief Turns on the specified LED.
 *
 * This function turns on a specific LED by its index.
 *
 * @param led Index of the LED to turn on.
 * @return true if the operation was successful, false otherwise.
 */
bool LEDs_SetOn(int led);

/**
 * @brief Turns on all LEDs.
 *
 * This function turns on all the LEDs connected to the port.
 */
void LEDs_SetAllOn(void);

/**
 * @brief Checks if the specified LED is on.
 *
 * This function verifies whether a particular LED is currently turned on.
 *
 * @param led Index of the LED to check.
 * @return true if the LED is on, false otherwise.
 */
bool LEDs_IsOn(int led);

#endif // LEDS_H
