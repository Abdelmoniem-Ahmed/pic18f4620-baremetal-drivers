/**
 * @file application.h
 * @brief Application layer header file.
 *
 * This file contains the application layer interface
 * and initialization function declarations.
 *
 * The application layer uses MCAL and ECUAL drivers
 * to demonstrate and test system functionality.
 *
 * @author Abdelmoniem Ahmed
 * @linkedin <- https://www.linkedin.com/in/abdelmoniem-ahmed/ ->
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */

#include"compiler.h"
#include"device_config.h"
#include"std_libraries.h"
#include"std_types.h"
#include"hal_gpio.h"
#include"ecu_layer_init.h"
#include"hal_eeprom.h"
#include"hal_adc.h"
#include"Timer0.h"
#include"timer1.h"
#include"Timer2.h"
#include"Timer3.h"
#include"CCP.h"
#include"hal_eusart.h"
#include"SPI_APIs.h"
#include"I2C_APIs.h"
#include"mcal_externl_interrupt.h"
#include"mcal_internal_interrupt.h"
#include"mcal_interrupt_config.h"
#include"mcal_interrupt_gen_cfg.h"
#include"mcal_interrupt_manager.h"

/* Example Applications */

#include"Example_projects/7-Segment/7_segment_app.h"
#include"Example_projects/Charachter_LCD/Chr_LCD_app.h"
#include"Example_projects/LED/Led_Blink_app.h"
#include"Example_projects/Matrix_keypad/Matrix_Keypad_app.h"
/* Both in the Smart Home Project */
#include"Example_projects/Smart_Home/Smart_Home_app.h"
#include "Example_projects/Smart_Home/Slave_MCU/Slave_MCU_main_app.h"

/* Section: Macro Declarations */

#define WORKING_APPLICATION                 0x01
#define NOT_WORKING_APPLICATION             0x00

#define SMART_HOME_APP                      WORKING_APPLICATION
#define MATRIX_KEYPAD_APP                   NOT_WORKING_APPLICATION
#define SEVEN_SEGMENT_APP                   NOT_WORKING_APPLICATION
#define CHR_LCD_APP                         NOT_WORKING_APPLICATION
#define LED_BLINK_APP                       NOT_WORKING_APPLICATION
#define LED_BLINK_HAL_APP                   NOT_WORKING_APPLICATION

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

/**
 * @brief Initialize the application layer.
 *
 * This function is responsible for initializing
 * all application-level modules and ECU layers
 * before entering the main execution loop.
 */
void application_initialize(void);

#endif	/* APPLICATION_H */

