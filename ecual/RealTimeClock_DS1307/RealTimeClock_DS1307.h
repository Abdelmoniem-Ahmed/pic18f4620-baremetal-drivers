/**
 * @file    RealTimeClock_DS1307.h
 * @brief   DS1307 Real-Time Clock (RTC) ECUAL driver interface
 *
 * @details
 * This module provides a high-level interface for communicating with
 * the DS1307 Real-Time Clock using the I2C protocol.
 *
 * The driver allows the application layer to read the current
 * date and time stored inside the DS1307 registers.
 *
 * The DS1307 communication is performed through the MSSP I2C
 * driver located in the MCAL layer.
 *
 * Supported features:
 *  - Read current time (hours, minutes, seconds)
 *  - Read current date (day, month, year)
 *
 * Notes:
 *  - DS1307 stores time values in BCD format.
 *  - Conversion to decimal format should be handled by the application layer if required.
 *
 * Layer      : ECUAL
 * Target MCU : PIC18F4620
 * Communication : I2C (MSSP)
 *
 * @author   Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @date     2026
 */

#ifndef REALTIMECLOCK_DS1307_H
#define	REALTIMECLOCK_DS1307_H

/* Section : Includes */

#include "../../mcal/I2C/I2C_APIs.h"

/* Section : Macro Declaration */

#define REAL_TIME_CLOCK_DS1307_ADDRESS          0x68

#define SECONDS_REGISTER_ADDRESS                0x00
#define MINUTES_REGISTER_ADDRESS                0x01
#define HOURS_REGISTER_ADDRESS                  0x02

/*  The day-of-week register increments at midnight. Values that
    correspond to the day of week are user-defined but must be sequential 
    (i.e., if 1 equals Sunday, then 2 equals Monday, and so on.) 
 */
#define DAY_REGISTER_ADDRESS                    0x03    /* For Now, Not Used */

/* The day-of-month register */
#define DATE_REGISTER_ADDRESS                   0x04
#define MONTH_REGISTER_ADDRESS                  0x05
#define YEAR_REGISTER_ADDRESS                   0x06


/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/**
 * @brief DS1307 date and time structure
 *
 * This structure holds the date and time values read from
 * the DS1307 RTC registers.
 *
 * All values are returned exactly as stored in the RTC registers
 * (BCD format).
 */
typedef struct{
    uint8 Hours;
    uint8 Minutes;
    uint8 Seconds;
    uint8 Year;
    uint8 Month;
    uint8 Day;
}RealTimeClock_DS1307_t;

/* Section : Function Declarations */

/**
 * @brief Read current date and time from the DS1307 RTC
 *
 * @param time Pointer to structure that will hold the date and time.
 *
 * @return Std_ReturnType
 *         - E_OK     : Operation successful
 *         - E_NOT_OK : Null pointer or communication failure
 *
 * @note
 * The function reads the following DS1307 registers:
 *  - Seconds  (0x00)
 *  - Minutes  (0x01)
 *  - Hours    (0x02)
 *  - Day      (0x04)
 *  - Month    (0x05)
 *  - Year     (0x06)
 */

Std_ReturnType RealTimeClock_DS1307_Get_Date_Time(RealTimeClock_DS1307_t * time);

#endif	/* REALTIMECLOCK_DS1307_H */

