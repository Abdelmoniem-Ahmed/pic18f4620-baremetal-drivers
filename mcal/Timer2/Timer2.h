/**
 * @file    hal_timer2.h
 * @author  Abdelmoniem Ahmed
 * @brief   Timer2 Driver Interface for PIC18F4620
 *
 * @details
 * This file defines the interface for the Timer2 driver.
 * The driver provides a configurable interface for the Timer2 peripheral,
 * supporting 8-bit timer operation, prescaler and postscaler configuration,
 * preload value, and optional interrupt-driven execution via a callback function.
 *
 * The driver follows MCAL principles, separating configuration, control, and
 * runtime services, and is designed to be MISRA-friendly and maintainable.
 *
 * Layer  : MCAL
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : Includes */
     
#include"std_types.h"
#include"hal_gpio.h"
#include"mcal_internal_interrupt.h"

/* Section : Macro Declaration */

#define TIMER2_ENABLE_CFG                    0X01
#define TIMER2_DISABLE_CFG                   0X00

/* Section : Macro Functions Declarations */

#define TIMER2_ENABLE()                         (T2CONbits.TMR2ON = TIMER2_ENABLE_CFG)
#define TIMER2_DISABLE()                        (T2CONbits.TMR2ON = TIMER2_DISABLE_CFG)

/* Section : Data Types Declarations */

/**
 * @enum timer2_prescaler_select_t
 * @brief Timer2 prescaler selection options
 *
 * @details
 * Determines the prescaler division applied to the Timer2 input clock.
 * This affects the timer tick frequency and overflow interval.
 */
typedef enum{
    timer2_prescaler_div_1   = 0 ,
    timer2_prescaler_div_4 ,       
    timer2_prescaler_div_16        
}timer2_prescaler_select_t;

/**
 * @enum timer2_postscaler_select_t
 * @brief Timer2 postscaler selection options
 *
 * @details
 * Defines the number of Timer2 overflows required before a TMR2 interrupt
 * is generated. The postscaler allows for longer periodic intervals without
 * software counting.
 */
typedef enum{
    timer2_postscaler_div_1  = 0 ,
    timer2_postscaler_div_2,
    timer2_postscaler_div_3,
    timer2_postscaler_div_4,
    timer2_postscaler_div_5, 
    timer2_postscaler_div_6,
    timer2_postscaler_div_7,
    timer2_postscaler_div_8,
    timer2_postscaler_div_9,  
    timer2_postscaler_div_10,
    timer2_postscaler_div_11,
    timer2_postscaler_div_12, 
    timer2_postscaler_div_13,
    timer2_postscaler_div_14,
    timer2_postscaler_div_15,
    timer2_postscaler_div_16        
}timer2_postscaler_select_t;

/**
 * @struct timer2_t
 * @brief Timer2 configuration structure
 *
 * @details
 * Encapsulates all configurable parameters required to initialize and control
 * the Timer2 peripheral. This structure allows the user to:
 *  - Select prescaler and postscaler values
 *  - Provide a preload value for precise timing intervals
 *  - Assign a callback function for interrupt-driven execution (optional)
 *  - Specify interrupt priority if priority levels are enabled
 *
 * @note
 * The preload value is reloaded automatically on every Timer2 overflow.
 */
typedef struct{
    timer2_prescaler_select_t prescaler_division ;
    timer2_postscaler_select_t postscaler_division ; 
#if   TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR_InterruptHandler) (void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;
#endif
#endif 
    uint8 preloaded_value ;
}timer2_t;

/* Section : Function Declarations */

/**
 * @brief Initialize Timer2 peripheral
 *
 * @details
 * Configures Timer2 with the user-defined settings:
 *  - Prescaler and postscaler values
 *  - Preload value for periodic timing
 *  - Optional interrupt with callback function
 *  - Optional interrupt priority if enabled
 *
 * The Timer2 counter is disabled during initialization to prevent spurious counts.
 * If interrupts are enabled, the callback is assigned and the global/peripheral
 * interrupts are configured according to the selected priority.
 *
 * @param timer Pointer to a `timer2_t` configuration structure
 * @retval E_OK     Initialization was successful
 * @retval E_NOT_OK Invalid pointer or configuration provided
 */
Std_ReturnType timer2_init(const timer2_t * timer);

/**
 * @brief Deinitialize Timer2 peripheral
 *
 * @details
 * Disables Timer2 and, if enabled, its interrupt. Clears any active configuration
 * to ensure the timer is in a known reset state.
 *
 * @param timer Pointer to a `timer2_t` configuration structure
 * @retval E_OK     Deinitialization was successful
 * @retval E_NOT_OK Invalid pointer provided
 */
Std_ReturnType timer2_Deinit(const timer2_t * timer);

/**
 * @brief Read the current Timer2 counter value
 *
 * @details
 * Retrieves the current 8-bit Timer2 register value. This value represents
 * the timer count at the time of the read. Useful for polling or timestamping.
 *
 * @param timer Pointer to a `timer2_t` configuration structure
 * @param time  Pointer to a variable where the current timer value will be stored
 * @retval E_OK     Value read successfully
 * @retval E_NOT_OK Invalid pointer(s) provided
 */
Std_ReturnType timer2_Read_Value(const timer2_t * timer , uint8 * time);

/**
 * @brief Write a value to the Timer2 counter register
 *
 * @details
 * Overwrites the current Timer2 counter with a new value. This allows
 * dynamic adjustment of timing intervals or immediate preload without
 * waiting for an overflow.
 *
 * @param timer Pointer to a `timer2_t` configuration structure
 * @param data  8-bit value to write to the Timer2 counter register
 * @retval E_OK     Value written successfully
 * @retval E_NOT_OK Invalid pointer provided
 */
Std_ReturnType timer2_Write_Value(const timer2_t * timer , uint8 data);


#endif	/* HAL_TIMER2_H */
