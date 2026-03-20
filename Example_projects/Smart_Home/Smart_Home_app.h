
#ifndef SMART_HOME_APP_H
#define	SMART_HOME_APP_H

/********************** Includes **********************/
#include<string.h>

#include"../../mcal/EEPROM/hal_eeprom.h"
#include"../../mcal/EUSART/hal_eusart.h"
#include"../../mcal/I2C/I2C_APIs.h"
#include"../../mcal/Timer0/Timer0.h"
#include"../../ecual/ecu_layer_init.h"


/********************** Macro Declaration **********************/
#define SLAVE_ADDRESS                   0x70

/* I2C slave addresses for two EEPROM devices (if applicable) */
#define EEPROM1_ADDRESS                 0x50
#define EEPROM2_ADDRESS                 0x51

#define MAX_TEMP_VAL_ADDRESS            0x00
#define MIN_TEMP_VAL_ADDRESS            0x01
#define LAST_TEMP_VAL_ADDRESS           0x02

#define PASSWORD_FAILED                 0x00
#define PASSWORD_PASSED                 0x01

#define MAX_PASSWORD_ATTEMPT            0x03
#define MAX_PASSWORD_DIGIT              10

/********************** Data Types Declaration **********************/

typedef enum{
    PASSWORD_SHOW_PROMPT,
    PASSWORD_READING,
    PASSWORD_CHECK,
    PASSWORD_GRANTED,
    PASSWORD_DENIED,
    PASSWORD_LOCKED        
}password_state_t;

/********************** Function Declaration **********************/
void Smart_Home_App(void);

#endif	/* SMART_HOME_APP_H */

