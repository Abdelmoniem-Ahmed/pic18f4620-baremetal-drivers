/**
 * @file    : Temperature_Sensor_TC74.c
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

#include"Temperature_Sensor_TC74.h"

/* Function Definition */

Std_ReturnType TempSensor_TC74_Read_Temp(uint8 sensor_address ,sint8 *temp){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == temp){
        ret = E_NOT_OK;
    }
    else{
        ret = MSSP_I2C_Read_Byte_Register(sensor_address,TEMP_REGISTER_ADDRESS,temp);
    }
    
    return ret;
}
