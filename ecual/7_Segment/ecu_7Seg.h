/* 
 * @file    ecu_7Seg.h
 * @brief   7-Segment ECUAL driver interface
 *
 * @details
 * This module provides high-level APIs to control 4-bit 7-segment displays.
 * Supports common-anode and common-cathode segment types.
 * 
 * GPIO initialization and writing is done via the HAL GPIO driver.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 *
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @date    2026
 */

#ifndef ECU_7SEG_H
#define	ECU_7SEG_H

/* Section : Includes */

#include"hal_gpio.h"

/* Section : Macro Declaration */


#define SEGMENT_PIN0 0 
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3


/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/**
 * @enum segment_type_t
 * @brief Defines the type of 7-segment display
 */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

/**
 * @struct segment_t
 * @brief Configuration structure for 7-segment display
 *
 * @details
 * Holds GPIO pin configuration for 4 data lines and the segment type.
 */
typedef struct{
    pin_config_t segment_pins[4] ;
    segment_type_t segment_type ;
}segment_t;



/* Section : Function Declarations */

/**
 * @brief Initialize 7-segment display pins as output
 *
 * @param seg Pointer to 7-segment configuration structure
 *
 * @return Std_ReturnType
 *         - E_OK     : Pins initialized successfully
 *         - E_NOT_OK : Null pointer provided
 *
 * @note
 * Only initializes the 4 data pins. Common pin handling should be done externally.
 */
Std_ReturnType seven_segment_initialize( segment_t * seg);

/**
 * @brief Write a number (0-9) to the 7-segment display
 *
 * @param seg Pointer to 7-segment configuration structure
 * @param number Number to display (0-9)
 *
 * @return Std_ReturnType
 *         - E_OK     : Number written successfully
 *         - E_NOT_OK : Invalid pointer or number > 9
 *
 * @note
 * This function directly writes to the 4 segment pins.
 * The caller must ensure the correct segment type (common anode/cathode) is handled externally.
 */
Std_ReturnType seven_segment_write_number(const segment_t * seg , uint8 number );


#endif	/* ECU_7SEG_H */

