/**
 * @file    : Temperature_Sensor_TC74.h
 * @brief   : TC74 Digital Temperature Sensor Driver Interface
 *
 * @details :   Provides a high-level interface to read temperature data from
 *              the Microchip TC74 digital temperature sensor via I2C.
 * 
 *              The TC74 returns temperature as an 8-bit signed value representing
 *              temperature in degrees Celsius.
 * 
 * Layer         : ECUAL
 * Target        : PIC18F4620
 * Communication : I2C (MSSP)
 * @author  : Abdelmoniem Ahmed
 * @LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
 *
 */

#ifndef TEMPERATURE_SENSOR_TC74_H
#define	TEMPERATURE_SENSOR_TC74_H

/*************** Includes ***************/
#include"../../mcal/I2C/I2C_APIs.h"

/*************** Macro Declarations ***************/
#define TEMP_SENSOR_ADDRESS             0x4D
#define TEMP_REGISTER_ADDRESS           0x00

/*************** Macro Functions Declarations ***************/

/*************** Data Type Declarations ***************/

/*************** Function Declarations ***************/

/**
 * @brief Reads the temperature value from the TC74 sensor
 *
 * @details
 * This function reads the temperature register (0x00) from the TC74
 * digital temperature sensor via the I2C bus. The TC74 returns the
 * temperature as an 8-bit signed value representing temperature in
 * degrees Celsius.
 *
 * The function performs the following I2C sequence:
 *  - START condition
 *  - Send slave address with WRITE
 *  - Send temperature register address (0x00)
 *  - REPEATED START
 *  - Send slave address with READ
 *  - Read temperature byte
 *  - STOP condition
 *
 * @param sensor_address  I2C slave address of the TC74 sensor
 * @param temp            Pointer to variable where the temperature
 *                        value will be stored
 *
 * @return Std_ReturnType
 *         - E_OK     : Temperature successfully read
 *         - E_NOT_OK : Communication failure or NULL pointer
 *
 * @note
 * The returned temperature is in degrees Celsius and stored
 * as an 8-bit signed value.
 *
 * Example:
 * @code
 * uint8 temperature = 0;
 * TempSensor_TC74_Read_Temp(TEMP_SENSOR_ADDRESS, &temperature);
 * @endcode
 */
Std_ReturnType TempSensor_TC74_Read_Temp(uint8 sensor_address ,sint8 *temp);

#endif	/* TEMPERATURE_SENSOR_TC74_H */

