/* 
 * @file    ecu_DC_motor.h
 * @brief   DC Motor ECUAL driver interface
 *
 * @details
 * Provides high-level APIs to control a DC motor using two GPIO pins.
 * Supports forward, backward, and stop operations.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : Includes */

#include"hal_gpio.h"

/* Section : Macro Declaration */

#define DC_MOTOR_PIN1  0x00U            /**< Motor control pin 1 index */
#define DC_MOTOR_PIN2  0x01U            /**< Motor control pin 2 index */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/**
 * @struct dc_motor_t
 * @brief DC motor configuration structure
 *
 * @details
 * Holds the two GPIO pins controlling motor direction.
 */
typedef struct{
    pin_config_t dc_motor[2];
}dc_motor_t;

/* Section : Function Declarations */

/**
 * @brief Initialize DC motor GPIO pins
 * 
 * @param motor Pointer to DC motor configuration
 * 
 * @return Std_ReturnType
 *         - E_OK     : Initialization successful
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t * motor);

/**
 * @brief Rotate DC motor forward
 */
Std_ReturnType dc_motor_move_forward(dc_motor_t * motor);

/**
 * @brief Rotate DC motor backward
 */
Std_ReturnType dc_motor_move_backward(dc_motor_t * motor);

/**
 * @brief Stop DC motor
 */
Std_ReturnType dc_motor_stop(dc_motor_t * motor);

#endif	/* ECU_MOTOR_H */

