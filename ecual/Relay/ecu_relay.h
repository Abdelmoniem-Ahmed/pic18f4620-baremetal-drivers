/* 
 * @file    ecu_relay.h
 * @brief   Relay ECUAL driver interface
 *
 * @details
 * Provides high-level APIs to initialize and control a relay via a GPIO pin.
 * Supports ON, OFF, and toggle operations.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */

#include"hal_gpio.h"

/* Section : Macro Declaration */

#define RELAY_ON_STATUS    0x01U            /**< Relay ON logic level */
#define RELAY_OFF_STATUS   0x00U            /**< Relay OFF logic level */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/**
 * @struct relay_t
 * @brief Relay configuration structure
 *
 * @details
 * Holds the port, pin, and current status of a relay.
 */
typedef struct{
    uint8 relay_port   : 4;
    uint8 relay_pin    : 3;
    uint8 relay_status : 1;
}relay_t;

/* Section : Function Declarations */

/**
 * @brief Initialize a relay GPIO pin
 *
 * @param relay_data Pointer to relay configuration
 * @return Std_ReturnType
 *         - E_OK     : Initialization successful
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType relay_initialize(const relay_t * relay_data );

/**
 * @brief Turn relay ON
 */
Std_ReturnType relay_turn_on(relay_t * relay_data );

/**
 * @brief Turn relay OFF
 */
Std_ReturnType relay_turn_off(relay_t * relay_data );

/**
 * @brief Toggle relay state
 */
Std_ReturnType relay_turn_toggle(relay_t * relay_data );


#endif	/* ECU_RELAY_H */

