/**
 * @file    RealTimeClock_DS1307.c
 * @brief   DS1307 Real-Time Clock driver implementation
 *
 * @details
 * Implements the high-level functions used to communicate
 * with the DS1307 RTC device over the I2C bus.
 *
 * Internal helper functions are used to perform
 * register-level I2C transactions.
 */

#include "RealTimeClock_DS1307.h"

/* Function Definiton */

Std_ReturnType RealTimeClock_DS1307_Get_Date_Time(RealTimeClock_DS1307_t * time){
    Std_ReturnType ret = E_OK;
    
    if(NULL == time){
        ret = E_NOT_OK;
    }
    else{
        ret = MSSP_I2C_Read_Byte_Register(  REAL_TIME_CLOCK_DS1307_ADDRESS ,
                                        SECONDS_REGISTER_ADDRESS ,
                                        &(time->Seconds) );
        
        ret = MSSP_I2C_Read_Byte_Register(  REAL_TIME_CLOCK_DS1307_ADDRESS ,
                                        MINUTES_REGISTER_ADDRESS ,
                                        &(time->Minutes) );
        
        ret = MSSP_I2C_Read_Byte_Register(  REAL_TIME_CLOCK_DS1307_ADDRESS ,
                                        HOURS_REGISTER_ADDRESS ,
                                        &(time->Hours) );
        ret = MSSP_I2C_Read_Byte_Register(  REAL_TIME_CLOCK_DS1307_ADDRESS ,
                                        DATE_REGISTER_ADDRESS ,
                                        &(time->Day) );
        ret = MSSP_I2C_Read_Byte_Register(  REAL_TIME_CLOCK_DS1307_ADDRESS ,
                                        MONTH_REGISTER_ADDRESS ,
                                        &(time->Month) );
        
        ret = MSSP_I2C_Read_Byte_Register(  REAL_TIME_CLOCK_DS1307_ADDRESS ,
                                        YEAR_REGISTER_ADDRESS ,
                                        &(time->Year) );
    }     
    return ret ;
}
