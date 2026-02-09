/**
 * @file ecu_Chr_lcd.h
 * @brief Character LCD ECUAL driver interface
 *
 * @details
 * This module provides high-level APIs for controlling HD44780-compatible
 * character LCD displays using either 4-bit or 8-bit data interface modes.
 *
 * The driver is implemented as an ECUAL layer and relies only on the GPIO
 * MCAL driver. No direct access to microcontroller registers is performed
 * inside this module.
 *
 * Supported features:
 * - 4-bit and 8-bit LCD operation
 * - Command and data transmission
 * - Cursor positioning
 * - String display
 * - Custom character (CGRAM) handling
 *
 * Design notes:
 * - The driver is blocking and polling-based
 * - LCD busy flag is not read; fixed delays are used instead
 * - Clock configuration is expected to be handled by the application
 *
 * Layer: ECUAL
 * Target MCU: PIC18F4620
 *
 * @author Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @date 2026
 */


#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H



/* Section : Includes */

#include"ecu_Chr_lcd_cfg.h"
#include"hal_gpio.h"

/* Section : Macro Declaration */

/**
 * @def _LCD_CLEAR
 * @brief Clear LCD display and reset cursor position
 */
#define _LCD_CLEAR                          0x01
/**
 * @def _LCD_RETURN_HOME
 * @brief Return cursor to home position
 */
#define _LCD_RETURN_HOME                    0x02
/**
 * @def _LCD_ENTRY_MODE
 * @brief Set cursor move direction and display shift
 */
#define _LCD_ENTRY_MODE                     0x06
/**
 * @def _LCD_CURSOR_OFF_DISPLAY_ON
 * @brief Display ON, cursor OFF
 */
#define _LCD_CURSOR_OFF_DISPLAY_ON          0x0C
/**
 * @def _LCD_CURSOR_OFF_DISPLAY_OFF
 * @brief Display OFF, cursor OFF
 */
#define _LCD_CURSOR_OFF_DISPLAY_OFF         0x08
/**
 * @def _LCD_CURSOR_ON_BLIN_ON
 * @brief Display ON, cursor ON, blinking enabled
 */
#define _LCD_CURSOR_ON_BLIN_ON              0x0F
/**
 * @def _LCD_CURSOR_ON_BLIN_OFF
 * @brief Display ON, cursor ON, blinking disabled
 */
#define _LCD_CURSOR_ON_BLIN_OFF             0x0E
/**
 * @def _LCD_DISPLAY_SHIFT_RIGHT
 * @brief Shift entire display to the right
 */
#define _LCD_DISPLAY_SHIFT_RIGHT            0x1C
/**
 * @def _LCD_DISPLAY_SHIFT_LEFT
 * @brief Shift entire display to the left
 */
#define _LCD_DISPLAY_SHIFT_LEFT             0x18
/**
 * @def _LCD_8BIT_MODE_2LINE
 * @brief Configure LCD for 8-bit, 2-line mode
 */
#define _LCD_8BIT_MODE_2LINE                0x38
/**
 * @def _LCD_4BIT_MODE_2LINE
 * @brief Configure LCD for 4-bit, 2-line mode
 */
#define _LCD_4BIT_MODE_2LINE                0x28
/**
 * @def _LCD_CGRAM_START
 * @brief Start address of CGRAM
 */
#define _LCD_CGRAM_START                    0x40
/**
 * @def _LCD_DDRAM_START
 * @brief Start address of DDRAM
 */
#define _LCD_DDRAM_START                    0x80


/**
 * @def ROW1
 * @brief First row of LCD display
 */
#define ROW1                                1
/**
 * @def ROW2
 * @brief Second row of LCD display
 */
#define ROW2                                2
/**
 * @def ROW3
 * @brief Third row of LCD display
 */
#define ROW3                                3
/**
 * @def ROW4
 * @brief Fourth row of LCD display
 */
#define ROW4                                4

/* Section : Macro Functions Declarations */


/* Section : Data Types Declarations */

#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_4BIT_MODE_ENABLE

/**
 * @struct chr_lcd_4bit_t
 * @brief Character LCD configuration structure (4-bit mode)
 *
 * @details
 * This structure defines all GPIO connections required
 * to interface with an HD44780-compatible LCD in 4-bit mode.
 *
 * Pins:
 * - RS : Register Select (Command/Data)
 * - EN : Enable signal
 * - DATA[4] : LCD data lines (D4?D7)
 *
 * @note
 * All pins must be configured as OUTPUT before initialization.
 */

typedef struct{
    pin_config_t lcd_rs ;
    pin_config_t lcd_en ;
    pin_config_t lcd_data[4] ;
}chr_lcd_4bit_t;

#elif CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_8BIT_MODE_ENABLE

/**
 * @struct chr_lcd_8bit_t
 * @brief Character LCD configuration structure (8-bit mode)
 *
 * @details
 * This structure defines all GPIO connections required
 * to interface with an HD44780-compatible LCD in 8-bit mode.
 *
 * Pins:
 * - RS : Register Select
 * - EN : Enable signal
 * - DATA[8] : LCD data lines (D0?D7)
 *
 * @note
 * All pins must be configured as OUTPUT before initialization.
 */

typedef struct{
    pin_config_t lcd_rs ;
    pin_config_t lcd_en ;
    pin_config_t lcd_data[8] ;
}chr_lcd_8bit_t;

#endif

/* Section : Function Declarations */

#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_4BIT_MODE_ENABLE

/**
 * @brief Initialize character LCD in 4-bit mode
 *
 * @param lcd Pointer to LCD configuration structure
 *
 * @return Std_ReturnType
 *         - E_OK     : Initialization successful
 *         - E_NOT_OK : Invalid parameter
 *
 * @note
 * GPIO pins must be configured as output.
 * Clock configuration must be done by the application.
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t * lcd );

/**
 * @brief Send command to LCD in 4-bit mode
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t * lcd , uint8 command );

/**
 * @brief Send character data to LCD in 4-bit mode
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t * lcd , uint8 data);

/**
 * @brief Send character to specific position in 4-bit mode
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column ,  uint8 data);

/**
 * @brief Send string to LCD in 4-bit mode
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t * lcd , uint8 *str );

/**
 * @brief Send string to specific position in 4-bit mode
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column, uint8 *str );

/**
 * @brief Send custom character to LCD in 4-bit mode
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t * lcd , uint8 row 
                                       , uint8 column , const uint8 _chr[] , uint8 mem_position );


#elif CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_8BIT_MODE_ENABLE

/**
 * @brief Initialize the character LCD module
 *
 * @details
 * This function performs:
 * - GPIO initialization
 * - LCD power-on initialization sequence
 * - LCD function set
 * - Display control configuration
 *
 * @param lcd Pointer to LCD configuration structure
 *
 * @return Std_ReturnType
 * - E_OK     : Initialization successful
 * - E_NOT_OK : NULL pointer or invalid configuration
 *
 * @note
 * LCD busy flag is NOT used.
 * Fixed delays are applied according to datasheet.
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t * lcd );

/**
 * @brief Send command to LCD in 8-bit mode
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t * lcd , uint8 command );

/**
 * @brief Send character data to LCD in 8-bit mode
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t * lcd , uint8 data);

/**
 * @brief Send character to specific position in 8-bit mode
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column ,  uint8 data);

/**
 * @brief Send string to LCD in 8-bit mode
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t * lcd , uint8 *str );

/**
 * @brief Send string to specific position in 8-bit mode
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column, uint8 *str );

/**
 * @brief Send custom character to LCD in 8-bit mode
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t * lcd , uint8 row 
                                       , uint8 column , const uint8 _chr[] , uint8 mem_position );

#endif


/**
 * @brief Convert uint8 value to string
 *
 * @param data Numeric value
 * @param str Pointer to output string buffer
 *
 * @return Std_ReturnType
 */
Std_ReturnType convert_byte_to_string(uint8 data , uint8 *str);

/**
 * @brief Convert uint16 value to decimal string
 *
 * @param data Numeric value
 * @param str Pointer to output string buffer
 *
 * @return Std_ReturnType
 */
Std_ReturnType convert_short_to_string(uint16 data , uint8 *str);

/**
 * @brief Convert uint32 value to decimal string
 *
 * @param data Numeric value
 * @param str Pointer to output string buffer
 *
 * @return Std_ReturnType
 */
Std_ReturnType convert_int_to_string(uint32 data , uint8 *str);

#endif	/* ECU_CHR_LCD_H */

