/* 
 * @file    ecu_led.h
 * @brief   LED ECUAL driver interface
 *
 * @details
 * This module provides high-level APIs to control single LEDs using GPIO HAL services.
 * 
 * Each LED is represented by its port, pin, and initial logic state.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "hal_gpio.h"

/* Section : Data Types Declarations */

/**
 * @struct led_t
 * @brief LED configuration structure
 *
 * @details
 * Holds the port, pin, and current logic level of an LED.
 * - port_name : Port of the LED (0-5)
 * - pin       : Pin of the LED (0-7)
 * - led_status: Current logic state (0=LOW, 1=HIGH)
 */
typedef struct {
    uint8 port_name   : 4 ;
    uint8 pin         : 3 ;
    uint8 led_status  : 1 ;
}led_t;

/* Section : Function Declarations */

/**
 * @brief Initialize the LED pin as output with initial logic
 * 
 * @param led Pointer to LED configuration structure
 * 
 * @return Std_ReturnType
 *         - E_OK     : LED initialized successfully
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType led_initialize(const led_t *led);

/**
 * @brief Turn on the LED (set logic HIGH)
 * 
 * @param led Pointer to LED configuration structure
 * 
 * @return Std_ReturnType
 *         - E_OK     : LED turned on successfully
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief Turn off the LED (set logic LOW)
 * 
 * @param led Pointer to LED configuration structure
 * 
 * @return Std_ReturnType
 *         - E_OK     : LED turned off successfully
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief Toggle the LED state (HIGH ? LOW)
 * 
 * @param led Pointer to LED configuration structure
 * 
 * @return Std_ReturnType
 *         - E_OK     : LED toggled successfully
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType led_turn_toggle(const led_t *led);


#endif	/* ECU_LED_H */

