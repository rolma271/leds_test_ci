/**
 * @file test_leds.c
 * @author Marco Rolon Radcenco
 *
 * @brief LED port test file for leds.c
 */

#include "leds.h"
#include "unity.h"

/**
 * Developed test:
 *
 1 - Initialize port
 2 - Turn on an individual LED
 3 - Turn off an individual LED
 4 - Turn on and off multiple LEDs
 5 - Turn off ALL LEDs
 6 - Turn on ALL LEDs
 7 - Check if an LED is on
 8 - Check if an LED is off
 9 - Check null port creation
 10 - Checking within boundaries
 11 - Checking outside boundaries: leds on
 11 - Checking outside boundaries: leds off
 */

static int16_t _port_virtual; /**< Simulated port for testing */

/**
 * @brief Runs before each test case.
 * If not defined, ceedling creates and uses it automatically.
 */
void setUp(void) {
    LEDs_Create(&_port_virtual);
}

/**
 * @brief Runs after each test case.
 * If not defined, ceedling creates and uses it automatically.
 */
void tearDown(void) {
    // No cleanup needed after each test
}

/**
 * Tests
 */

// 1 - Initialize LEDs, all should be off
void test_leds_init_all_off(void) {
    uint16_t _port_virtual = 0xFFFF;
    TEST_ASSERT_TRUE(LEDs_Create(&_port_virtual));
    TEST_ASSERT_EQUAL_HEX16(0, _port_virtual);
}

// 2 - Turn on an individual LED
void test_leds_turn_on_individual_led(void) {
    TEST_ASSERT_TRUE(LEDs_SetOn(3));
    TEST_ASSERT_EQUAL_HEX16(1 << 2, _port_virtual);
}

// 3 - Turn off an individual LED
void test_leds_turn_off_individual(void) {
    TEST_ASSERT_TRUE(LEDs_SetOn(3));
    TEST_ASSERT_TRUE(LEDs_SetOff(3));
    TEST_ASSERT_EQUAL_HEX16(0, _port_virtual);
}

// 4 - Turn on and off multiple LEDs
void test_leds_turn_on_and_off_multiple(void) {
    TEST_ASSERT_TRUE(LEDs_SetOn(7));
    TEST_ASSERT_TRUE(LEDs_SetOn(5));
    TEST_ASSERT_TRUE(LEDs_SetOff(2));
    TEST_ASSERT_TRUE(LEDs_SetOff(7));
    TEST_ASSERT_EQUAL_HEX16(1 << 4, _port_virtual);
}

// 5 - Turn off all LEDs at once
void test_leds_turn_off_all(void) {
    LEDs_SetAllOff();
    TEST_ASSERT_EQUAL_HEX16(0, _port_virtual);
}

// 6 - Turn on all LEDs at once
void test_leds_turn_on_all(void) {
    LEDs_SetAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, _port_virtual);
}

// 7 - Check if an LED is on
void test_leds_check_if_led_is_on(void) {
    TEST_ASSERT_TRUE(LEDs_SetOn(1));
    TEST_ASSERT_TRUE(LEDs_IsOn(1));
}

// 8 - Check if an LED is off
void test_leds_check_if_off(void) {
    TEST_ASSERT_TRUE(LEDs_SetOff(1));
    TEST_ASSERT_FALSE(LEDs_IsOn(1));
}

// 9 - Test for null port
void test_leds_null_port(void) {
    uint16_t * virtual_port_null = NULL;
    TEST_ASSERT_FALSE(LEDs_Create(virtual_port_null));
}

// 10 - Test for checking within boundaries
void test_leds_check_within_limits(void) {
    TEST_ASSERT_TRUE(LEDs_SetOn(1));
    TEST_ASSERT_TRUE(LEDs_SetOn(16));

    TEST_ASSERT_EQUAL_HEX16((1 << 0) | (1 << 15), _port_virtual);
}

// 11 - Test for checking outside boundaries: on
void test_leds_check_outside_limits_on(void) {
    TEST_ASSERT_FALSE(LEDs_SetOn(0));
    TEST_ASSERT_FALSE(LEDs_SetOn(17));

    TEST_ASSERT_EQUAL_HEX16(0, _port_virtual);
}

// 11 - Test for checking outside boundaries: off
void test_leds_check_outside_limits_off(void) {
    TEST_ASSERT_FALSE(LEDs_SetOff(0));
    TEST_ASSERT_FALSE(LEDs_SetOff(17));

    TEST_ASSERT_EQUAL_HEX16(0, _port_virtual);
}
