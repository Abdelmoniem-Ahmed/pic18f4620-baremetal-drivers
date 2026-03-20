/**
 * @file ecu_layer_init.h
 * @brief ECUAL layer initialization for PIC18F microcontrollers
 *
 * @details
 * This module provides a high-level interface to initialize all
 * ECUAL drivers for your project, including LEDs, 7-segment, LCD,
 * keypad, motors, relays, RTC, EEPROM, and temperature sensors.
 *
 * Layer: ECUAL
 * Target: PIC18F4620
 *
 * @author Abdelmoniem Ahmed
 * @linkedin -> https://www.linkedin.com/in/abdelmoniem-ahmed/ <-
 *  */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */

#include"7_Segment/ecu_7Seg.h"
#include"Chr_LCD/ecu_Chr_lcd.h"
#include"LED/ecu_led.h"
#include"Matrix_Keypad/ecu_keypad.h"
#include"Motor/ecu_DC_motor.h"
#include"Relay/ecu_relay.h"
#include"RealTimeClock_DS1307/RealTimeClock_DS1307.h"
#include"EEPROM_24C02C/EEPROM_24C02C.h"
#include"Temperature_Sensor_TC74/Temperature_Sensor_TC74.h"

/* Section : Macro Declaration */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/* Section : Function Declarations */

/**
 * @brief Initialize all ECUAL layer modules
 *
 * @details
 * This function initializes all peripherals in the ECUAL layer.
 * Call this once at system startup.
 */
void initialize_ecu_layer(void);

#endif	/* ECU_LAYER_INIT_H */

