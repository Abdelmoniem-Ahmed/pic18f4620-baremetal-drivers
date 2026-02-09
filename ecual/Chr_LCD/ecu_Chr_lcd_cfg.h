/**
 * @file ecu_Chr_lcd_cfg.h
 * @brief Character LCD configuration file
 *
 * @details
 * This file contains all compile-time configuration options
 * for the Character LCD ECUAL driver.
 *
 * Configuration is handled using preprocessor macros to:
 * - Select LCD interface mode (4-bit or 8-bit)
 * - Enable or disable specific driver features at compile time
 *
 * This approach:
 * - Eliminates runtime overhead
 * - Ensures smaller code size
 * - Follows AUTOSAR-like configuration philosophy
 *
 * Layer: ECUAL
 * Target MCU: PIC18F4620
 *
 * @author Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @date 2026
 */

#ifndef ECU_CHR_LCD_CFG_H
#define	ECU_CHR_LCD_CFG_H

/* Section : Includes */

/* No includes required */

/* Section: Macro Declarations */


/**
 * @def CHR_LCD_4BIT_MODE_ENABLE
 * @brief Enable 4-bit LCD interface mode
 *
 * @note
 * Uses only 4 data pins (D4?D7).
 * Saves GPIO pins but requires two data transfers per byte.
 */
#define CHR_LCD_4BIT_MODE_ENABLE                0X01

/**
 * @def CHR_LCD_8BIT_MODE_ENABLE
 * @brief Enable 8-bit LCD interface mode
 *
 * @note
 * Uses full 8 data pins (D0?D7).
 * Faster data transfer but consumes more GPIO pins.
 */
#define CHR_LCD_8BIT_MODE_ENABLE                0X02


/**
 * @def CHR_LCD_4BIT_OR_8BIT_MODE_CFG
 * @brief Select LCD interface mode at compile time
 *
 * @details
 * Allowed values:
 * - CHR_LCD_4BIT_MODE_ENABLE
 * - CHR_LCD_8BIT_MODE_ENABLE
 *
 * @warning
 * Only ONE mode must be selected.
 * Changing this macro affects:
 * - Data structures
 * - API availability
 * - Internal driver implementation
 */
#define CHR_LCD_4BIT_OR_8BIT_MODE_CFG           CHR_LCD_8BIT_MODE_ENABLE

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */


#endif	/* ECU_CHR_LCD_CFG_H */

