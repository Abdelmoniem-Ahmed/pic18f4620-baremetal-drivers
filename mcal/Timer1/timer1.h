/**
 * @file    Timer1.h
 * @author  Abdelmoniem Ahmed
 * @brief   Timer1 Driver Interface
 *
 * @details
 * This file contains the interface definitions for the Timer1 driver.
 * The driver provides configuration, initialization, control, and runtime
 * services for the Timer1 peripheral of the PIC18F4620 microcontroller.
 *
 * Features:
 *  - Timer and Counter modes
 *  - 16-bit operation with preload and reload
 *  - Prescaler configuration (1:1, 1:2, 1:4, 1:8)
 *  - Optional interrupt support with callback mechanism
 *  - Synchronous / Asynchronous counter modes
 *  - Oscillator enable/disable
 *
 * Layer  : MCAL (Microcontroller Abstraction Layer)
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */


#ifndef TIMER1_H
#define	TIMER1_H

/* Section : Includes */
      
#include"std_types.h"
#include"hal_gpio.h"
#include"mcal_internal_interrupt.h"

/* Section : Macro Declaration */

/* Timer1 Mode Selection */
#define TIMER1_TIMER_MODE_CFG                0X00
#define TIMER1_COUNTER_MODE_CFG              0X01

/* Timer1 Enable/Disable */
#define TIMER1_ENABLE_CFG                    0X01
#define TIMER1_DISABLE_CFG                   0X00

/* Counter Sync/Async Mode */
#define TIMER1_ASYNC_COUNTER_MODE_CFG        0X01
#define TIMER1_SYNC_COUNTER_MODE_CFG         0X00

/* Timer1 Oscillator */
#define TIMER1_OSC_ENABLE                    0X01
#define TIMER1_OSC_DISABLE                   0X00

/* Register Read Mode */
#define TIMER1_RD_8BIT_MODE_CFG              0X00
#define TIMER1_RD_16BIT_MODE_CFG             0X01

/* Section : Macro Functions Declarations */

/* Enable / Disable Timer1 */
#define TIMER1_ENABLE()                         (T1CONbits.TMR1ON = TIMER1_ENABLE_CFG)
#define TIMER1_DISABLE()                        (T1CONbits.TMR1ON = TIMER1_DISABLE_CFG)

/* Select Timer or Counter Mode */
#define TIMER1_COUNTER_MODE()                   (T1CONbits.TMR1CS = TIMER1_COUNTER_MODE_CFG)
#define TIMER1_TIMER_MODE()                     (T1CONbits.TMR1CS = TIMER1_TIMER_MODE_CFG)

/* Counter Synchronization */
#define TIMER1_SYNC_COUNTER_SET()               (T1CONbits.T1SYNC = TIMER1_SYNC_COUNTER_MODE_CFG)
#define TIMER1_ASYNC_COUNTER_SET()              (T1CONbits.T1SYNC = TIMER1_ASYNC_COUNTER_MODE_CFG)

/* Oscillator Control */
#define TIMER1_OSC_MODE_ENABLE()                (T1CONbits.T1OSCEN = TIMER1_OSC_ENABLE)         
#define TIMER1_OSC_MODE_DISABLE()               (T1CONbits.T1OSCEN = TIMER1_OSC_DISABLE)                   

/* Prescaler Selection */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_)    (T1CONbits.T1CKPS = _PRESCALER_)

/* System Clock Status */
#define TIMER1_SYSTEM_CLK_STATUS()              (T1CONbits.T1RUN)

/* Register Read/Write Mode */
#define TIMER1_RD_8BIT_MODE_ENABLE()            (T1CONbits.RD16 = TIMER1_RD_8BIT_MODE_CFG)
#define TIMER1_RD_16BIT_MODE_ENABLE()           (T1CONbits.RD16 = TIMER1_RD_16BIT_MODE_CFG)

/* Section : Data Types Declarations */

/**
 * @brief Timer1 prescaler options
 */
typedef enum{
    timer1_prescaler_dive_1   = 0 ,
    timer1_prescaler_dive_2   = 1 ,
    timer1_prescaler_dive_4   = 2,        
    timer1_prescaler_dive_8   = 3         
}timer1_prescaler_select_t;

/**
 * @brief Timer1 Configuration Structure
 *
 * Used to configure Timer1 peripheral.
 * Includes preload value, prescaler, mode selection, oscillator, and optional interrupts.
 */
typedef struct {
    uint16 timer1_preload_value ;
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR_InterruptHandler) (void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;
#endif
#endif  
    timer1_prescaler_select_t prescaler_division ;
    uint8 timer1_mode               : 1 ;
    uint8 timer1_counter_mode       : 1 ;
    uint8 timer1_osc_cfg            : 1 ;
    uint8 timer1_reg_rw_mode        : 1 ;
    uint8 timer1_reserved           : 4 ; 
}timer1_t;

/* Section : Function Declarations */

/**
 * @brief Initialize Timer1 with the provided configuration
 * @param timer: Pointer to Timer1 configuration structure
 * @retval E_OK on success, E_NOT_OK on invalid parameters
 */
Std_ReturnType timer1_init(const timer1_t * timer);

/**
 * @brief Deinitialize Timer1, stop counting, and disable interrupts
 * @param timer: Pointer to Timer1 configuration structure
 * @retval E_OK on success, E_NOT_OK on invalid parameters
 */
Std_ReturnType timer1_Deinit(const timer1_t * timer);

/**
 * @brief Read the current Timer1 count value
 * @param timer: Pointer to Timer1 configuration structure
 * @param time: Pointer to store the read value
 * @retval E_OK on success, E_NOT_OK on invalid parameters
 */
Std_ReturnType timer1_Read_Value(const timer1_t * timer , uint16 * time);

/**
 * @brief Write a value to Timer1 registers
 * @param timer: Pointer to Timer1 configuration structure
 * @param data: 16-bit value to load into TMR1H:TMR1L
 * @retval E_OK on success, E_NOT_OK on invalid parameters
 */
Std_ReturnType timer1_Write_Value(const timer1_t * timer , uint16 data);

#endif	/* TIMER1_H */




