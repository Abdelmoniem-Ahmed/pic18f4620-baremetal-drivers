/**
 * @file    Timer0.h
 * @author  Abdelmoniem Ahmed
 * @brief   Timer0 Driver Interface
 *
 * @details
 * This file contains the interface definitions for the Timer0 driver.
 * The driver provides configuration, initialization, control, and runtime
 * services for the Timer0 peripheral of the PIC18F4620 microcontroller.
 *
 * Features:
 *  - Timer and Counter modes
 *  - 8-bit and 16-bit operation
 *  - Prescaler configuration
 *  - Interrupt support with callback mechanism
 *
 * Layer  : MCAL (Microcontroller Abstraction Layer)
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#ifndef TIMER0_H
#define	TIMER0_H

/* Section : Includes */
       
#include"std_types.h"
#include"hal_gpio.h"
#include"mcal_internal_interrupt.h"

/* Section : Macro Declaration */

/* Prescaler assignment configuration */
#define PRESCALER_ASSIGNED_CFG        0X00
#define PRESCALER_NOT_ASSIGNED_CFG    0x01

/* Clock source selection */
#define TIMER0_INTERNAL_CLK_SRC_CFG   0X00
#define TIMER0_EXTERNAL_CLK_SRC_CFG   0X01

/* External counter edge selection */
#define TIMER0_RISING_EDGE_CFG        0X00
#define TIMER0_FALLING_EDGE_CFG       0X01

/* Timer enable/disable */
#define TIMER0_ENABLE_CFG             0X01
#define TIMER0_DISABLE_CFG            0X00

/* Timer resolution */
#define TIMER0_8BIT_MODE_CFG          0X01
#define TIMER0_16BIT_MODE_CFG         0X00

/* Section : Macro Functions Declarations */

/* Enable/Disable Timer0 module */
#define TIMER0_ENABLE()                    (T0CONbits.TMR0ON = TIMER0_ENABLE_CFG)
#define TIMER0_DISABLE()                   (T0CONbits.TMR0ON = TIMER0_DISABLE_CFG)

/* Select Timer0 register size */
#define TIMER0_8BIT_Register_MODE_ENABLE()  (T0CONbits.T08BIT = TIMER0_8BIT_MODE_CFG)
#define TIMER0_16BIT_Register_MODE_ENABLE() (T0CONbits.T08BIT = TIMER0_16BIT_MODE_CFG)

/* Select Timer or Counter mode */
#define TIMER0_COUNTER_MODE()              (T0CONbits.T0CS = TIMER0_EXTERNAL_CLK_SRC_CFG)
#define TIMER0_TIMER_MODE()                (T0CONbits.T0CS = TIMER0_INTERNAL_CLK_SRC_CFG)

/* Select external counter edge */
#define TIMER0_RISING_EDGE_ENABLE()        (T0CONbits.T0SE = TIMER0_RISING_EDGE_CFG) 
#define TIMER0_FALLING_EDGE_ENABLE()       (T0CONbits.T0SE = TIMER0_FALLING_EDGE_CFG)

/* Prescaler assignment control */
#define PRESCALER_ASSIGNED()               (T0CONbits.PSA = PRESCALER_ASSIGNED_CFG)
#define PRESCALER_NOT_ASSIGNED()           (T0CONbits.PSA = PRESCALER_NOT_ASSIGNED_CFG)

/* Section : Data Types Declarations */

/**
 * @brief Timer0 prescaler division options
 */
typedef enum{
    timer0_prescaler_div_2   = 0 ,
    timer0_prescaler_div_4   = 1 ,
    timer0_prescaler_div_8   = 2,        
    timer0_prescaler_div_16  = 3,
    timer0_prescaler_div_32  = 4 ,
    timer0_prescaler_div_64  = 5 ,
    timer0_prescaler_div_128 = 6 , 
    timer0_prescaler_div_256 = 7 ,         
}timer0_prescaler_select_t;

/**
 * @brief Timer0 configuration structure
 */
typedef struct{
    timer0_prescaler_select_t prescaler_division ;      /* Prescaler division factor */
#if   TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR_InterruptHandler) (void);               /* ISR callback function */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;                    /* Interrupt priority */
#endif
#endif 
    uint16 timer0_preload_value;                        /* Preload value */
    uint8  clock_source        :1;                      /* Internal/External clock */
    uint8  prescaler_enable    :1;                      /* Prescaler enable */
    uint8  counter_edge_select :1;                      /* Rising/Falling edge */
    uint8  timer_resolution    :1;                      /* 8-bit or 16-bit mode */
    uint8  timer0_reserved     :4;                      /* Reserved */
}timer0_t;

/* Section : Function Declarations */

/**
 * @brief Initialize Timer0 with user configuration
 * @param timer Pointer to Timer0 configuration structure
 * @return Std_ReturnType (E_OK / E_NOT_OK)
 */
Std_ReturnType timer0_init(const timer0_t * timer);

/**
 * @brief Deinitialize Timer0 module
 * @return Std_ReturnType (E_OK)
 */
Std_ReturnType timer0_Deinit(void);

/**
 * @brief Read current Timer0 counter value
 * @param timer Pointer to Timer0 configuration structure
 * @param time Pointer to variable to store timer value
 * @return Std_ReturnType (E_OK / E_NOT_OK)
 */
Std_ReturnType timer0_Read_Value(const timer0_t * timer , uint16 * time);

/**
 * @brief Write value to Timer0 counter register
 * @param timer Pointer to Timer0 configuration structure
 * @param data Value to be written
 * @return Std_ReturnType (E_OK / E_NOT_OK)
 */
Std_ReturnType timer0_Write_Value(const timer0_t * timer , uint16 data);

#endif	/* TIMER0_H */

