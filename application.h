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
#include"ecu_layer_init.h"
#include"hal_gpio.h"
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

/* Section: Macro Declarations */

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
void application_intialize(void);

#endif	/* APPLICATION_H */

