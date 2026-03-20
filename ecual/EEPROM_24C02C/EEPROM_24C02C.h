/**
 * @file    EEPROM_24C02C.h
 * @brief   24C02C I2C EEPROM ECUAL Driver Interface
 *
 * @details
 * This header file provides a high-level interface for reading and writing
 * single bytes to a 24C02C EEPROM via I2C. It uses the MSSP I2C driver
 * located in the MCAL layer.
 *
 * Features:
 *  - Write a single byte to a memory address
 *  - Read a single byte from a memory address
 *
 * Layer      : ECUAL
 * Target MCU : PIC18F4620
 * Communication : I2C (MSSP)
 * Author     : Abdelmoniem Ahmed
 * LinkedIn   : https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date       : 2026
 */

#ifndef EEPROM_24C02C_H
#define	EEPROM_24C02C_H

/********************** Includes **********************/
#include"../../mcal/I2C/I2C_APIs.h"

/********************** Macro Declaration  **********************/

/********************** Function Declaration **********************/

/**
 * @brief Write a single byte to a 24C02C EEPROM memory address
 *
 * @param eeprom_address I2C slave address of the EEPROM (0x50 or 0x51)
 * @param mem_address    Memory address inside EEPROM to write (0x00 - 0xFF)
 * @param data           Byte of data to write
 *
 * @return Std_ReturnType
 *         - E_OK     : Write operation successful
 *         - E_NOT_OK : Communication failure or invalid pointer
 *
 * @note
 * A small delay (~5ms) is added after the write to allow the EEPROM
 * to complete its internal write cycle.
 */
Std_ReturnType EEPROM_24C02C_Write_Byte(uint8 eeprom_address , uint8 mem_address , uint8 data );

/**
 * @brief Read a single byte from a 24C02C EEPROM memory address
 *
 * @param eeprom_address I2C slave address of the EEPROM (0x50 or 0x51)
 * @param mem_address    Memory address inside EEPROM to read (0x00 - 0xFF)
 * @param data           Pointer to variable to store read data
 *
 * @return Std_ReturnType
 *         - E_OK     : Read operation successful
 *         - E_NOT_OK : Communication failure or invalid pointer
 */
Std_ReturnType EEPROM_24C02C_Read_Byte(uint8 eeprom_address , uint8 mem_address , uint8 *data );

#endif	/* EEPROM_24C02C_H */

