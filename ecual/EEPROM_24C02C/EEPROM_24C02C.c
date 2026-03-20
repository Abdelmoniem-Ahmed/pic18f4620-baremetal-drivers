/**
 * @file    EEPROM_24C02C.c
 * @brief   24C02C I2C EEPROM Driver Implementation
 *
 * @details
 * This source file implements functions for reading and writing single bytes
 * to the 24C02C EEPROM via I2C using the MSSP I2C driver.
 *
 * Layer      : ECUAL
 * Target MCU : PIC18F4620
 * Communication : I2C (MSSP)
 * Author     : Abdelmoniem Ahmed
 * LinkedIn   : https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date       : 2026
 */

#include"EEPROM_24C02C.h"

/********************** Function Definitions **********************/

Std_ReturnType EEPROM_24C02C_Write_Byte(uint8 eeprom_address , uint8 mem_address , uint8 data ){
    Std_ReturnType ret = E_NOT_OK;
       
    ret = MSSP_I2C_Write_Byte_Register(eeprom_address , mem_address , data);
    __delay_ms(5);    /**< Wait for EEPROM internal write cycle to complete */
    return ret;
}

Std_ReturnType EEPROM_24C02C_Read_Byte(uint8 eeprom_address , uint8 mem_address , uint8 *data ){
    Std_ReturnType ret = E_NOT_OK;

    ret = MSSP_I2C_Read_Byte_Register(eeprom_address , mem_address , data);
    
    return ret;
}
