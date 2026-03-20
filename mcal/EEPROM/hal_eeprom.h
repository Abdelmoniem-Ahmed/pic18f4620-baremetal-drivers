/**
 * @file   hal_eeprom.h
 * @author Monem
 * @brief  HAL Data EEPROM Driver for PIC18F4620
 *
 * @details
 * This file provides the interface for the internal Data EEPROM driver
 * of the PIC18F4620 microcontroller.
 *
 * The driver supports:
 *  - Byte read operation (Polling based)
 *  - Byte write operation (Polling based)
 *
 * Note:
 *  - The driver uses blocking (polling) technique.
 *  - Interrupts are temporarily disabled during the write unlock sequence
 *    to guarantee atomic operation.
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section : Includes */

#include"std_types.h"
#include"mcal_interrupt_config.h"

/* Section : Macro Declaration */

/**
 * @brief Select Data EEPROM memory space
 */
#define ACCESS_DATA_EEPROM_MEM   0x00
 
/**
* @brief Enable EEPROM write operation
*/
#define WRITE_ENABLE             0x01

/**
 * @brief Disable EEPROM write operation
 */
#define WRITE_DISABLE            0x00

/**
* @brief Initiate EEPROM write cycle
*/
#define WRITE_CYCLE_INITATE      0x01

/**
 * @brief Initiate EEPROM read cycle
 */
#define READ_CYCLE_INITIATE      0x01
   

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */



/* Section : Function Declarations */

/**
 * @brief  Reads a single byte from Data EEPROM
 *
 * @param  address   EEPROM address (0x000 – 0x3FF)
 * @param  Data      Pointer to store the read byte
 *
 * @return Std_ReturnType
 *         - E_OK      : Operation successful
 *         - E_NOT_OK  : Operation failed (invalid parameters)
 */
Std_ReturnType Data_EEPROM_Read_Byte(uint16 address , uint8 *Data);

/**
 * @brief  Writes a single byte to Data EEPROM
 *
 * @param  address   EEPROM address (0x000 – 0x3FF)
 * @param  Data      Byte to be written
 *
 * @return Std_ReturnType
 *         - E_OK      : Operation successful
 *         - E_NOT_OK  : Operation failed (invalid parameters)
 *
 * @note   This function uses polling until the write cycle completes.
 */
Std_ReturnType Data_EEPROM_Write_Byte(uint16 address , uint8 Data);

#endif	/* HAL_EEPROM_H */

