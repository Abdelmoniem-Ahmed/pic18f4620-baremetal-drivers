/**
 * @file ecu_layer_init.h
 * @brief GPIO HAL driver interface for PIC18F microcontrollers
 *
 * @details
 * This module provides high-level APIs for configuring and controlling
 * GPIO pins and ports using register-level access.
 *
 * Layer: ECUAL
 * Target: PIC18F
 *
 * @author Abdelmoniem Ahmed
 * @linkedin -> https://www.linkedin.com/in/abdelmoniem-ahmed/ <-
 * @date 2026
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */

#include"7_Segment/ecu_7Seg.h"
#include"Chr_LCD/ecu_Chr_lcd.h"
#include"LED/ecu_led.h"
#include"Matrix_Keypad/ecu_keypad.h"
#include"Motor/ecu_DC_motor.h"
#include"Relay/ecu_relay.h"

/* Section : Macro Declaration */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/* Section : Function Declarations */

/**
 * @brief Initialize the ECUAL layer.
 *
 * This function is responsible for initializing
 * all ECU layer modules 
 */
void initialize_ecu_layer(void);

#endif	/* ECU_LAYER_INIT_H */

