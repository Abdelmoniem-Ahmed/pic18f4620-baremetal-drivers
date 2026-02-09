/* 
 * @file    ecu_keypad.h
 * @brief   4x4 Matrix Keypad ECUAL driver interface
 *
 * @details
 * This module provides high-level APIs to initialize and read a 4x4 matrix keypad.
 * Each key press is detected by scanning rows and reading columns using GPIO HAL.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */


#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */

#include"hal_gpio.h"

/* Section : Macro Declaration */

#define KEYPAD_COLUMN 4         /**< Number of keypad rows */
#define KEYPAD_ROW 4            /**< Number of keypad columns */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/**
 * @struct keypad_t
 * @brief Keypad configuration structure
 *
 * @details
 * Holds the GPIO pins for rows and columns of the keypad.
 * - keypad_row_pins    : Array of row pins
 * - keypad_column_pins : Array of column pins
 */
typedef struct{
    pin_config_t keypad_column_pins[KEYPAD_COLUMN] ;
    pin_config_t keypad_row_pins[KEYPAD_ROW] ; 
}keypad_t;

/* Section : Function Declarations */

/**
 * @brief Initialize all keypad GPIO pins
 * 
 * @param keypad_obj Pointer to keypad configuration
 * 
 * @return Std_ReturnType
 *         - E_OK     : Keypad initialized successfully
 *         - E_NOT_OK : Null pointer provided
 */
Std_ReturnType keypad_initialize(const keypad_t * keypad_obj);

/**
 * @brief Scan keypad and return pressed key
 * 
 * @param keypad_obj Pointer to keypad configuration
 * @param value Pointer to store the detected key
 * 
 * @return Std_ReturnType
 *         - E_OK     : Key read successfully
 *         - E_NOT_OK : Null pointer provided
 *
 * @note If multiple keys are pressed simultaneously, the last detected key in scan order is returned.
 */
Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value );

#endif	/* ECU_KEYPAD_H */

