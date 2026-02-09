/**
 * @file    mcal_interrupt_config.h
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/Abdelmoniem-Ahmed/
 * @brief   MCAL Interrupt Configuration Definitions
 * @details This file contains common macros, configurations, and data types
 *          used by the MCAL interrupt module.
 *
 *          It provides:
 *          - Global interrupt enable/disable macros
 *          - Priority-based and non-priority interrupt control
 *          - Common interrupt status macros
 *          - Interrupt priority configuration data types
 *
 *          The actual enabling or disabling of specific interrupt sources
 *          is controlled through configuration files and peripheral drivers.
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Includes */

#include <xc.h>
#include "std_types.h"
#include"mcal_interrupt_gen_cfg.h"
#include "hal_gpio.h"

/* Section : Macro Declaration */

/**
 * @brief General interrupt enable/disable states
 */
#define INTERRUPT_ENABLE                 0x01
#define INTERRUPT_DISABLE                0x00

/**
 * @brief Interrupt occurrence status
 */
#define INTERRUPT_OCCUR                  0x01
#define INTERRUPT_NOT_OCCUR              0x00

/**
 * @brief Interrupt priority feature states
 */
#define INTERRUPT_PRIORITY_ENABLE        0x01
#define INTERRUPT_PRIORITY_DISABLE       0x00


/* Section : Macro Functions Declarations */

#if INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_PRIORITY_LEVELS_ENABLE

/* This Macro Will Enable Priority Feature */
#define INTERRUPT_PriorityFeatureEnable()       (RCONbits.IPEN = 1)

/* This Macro Will Disable Priority Feature " Enter Compatability Mode " */
#define INTERRUPT_PriorityFeatureDisable()       (RCONbits.IPEN = 0)

/* This Macro Will Enable HIGH Priority Global Interrupts  */
#define INTERRUPT_GlobalInterruptHighEnable()   (INTCONbits.GIEH = 1)

/* This Macro Will Disable HIGH Priority Global Interrupts  */
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH = 0)

/* This Macro Will Enable LOW Priority Global Interrupts  */
#define INTERRUPT_GlobalInterruptLowEnable()    (INTCONbits.GIEL = 1)

/* This Macro Will Disable LOW Priority Global Interrupts  */
#define INTERRUPT_GlobalInterruptLowDisable()   (INTCONbits.GIEL = 0)

#else

/* This Macro Will Enable All Global Interrupts  */
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE = 1)

/* This Macro Will Disable All Global Interrupts  */
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE = 0)

/* This Macro Will Enable "ALL PERIPHERAL" Interrupts  */
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE = 1)

/* This Macro Will Disable "ALL PERIPHERAL" Interrupts  */
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE = 0)

#endif

/* Section : Data Types Declarations */

/**
 * @brief Interrupt priority configuration type
 * @note  Used only when interrupt priority feature is enabled
 */
typedef enum{
    Interrupt_Low_Priority = 0,
    Interrupt_High_Priority        
}INTERRUPT_Priority_cfg;


/* Section : Function Declarations */



#endif	/* MCAL_INTERRUPT_CONFIG_H */




