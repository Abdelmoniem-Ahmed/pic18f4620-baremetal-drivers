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

#include "compiler.h"
#include "device_config.h"
#include "std_libraries.h"
#include "std_types.h"
#include "hal_gpio.h"

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

