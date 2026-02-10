/**
 * @file    Timer3.h
 * @author  Abdelmoniem Ahmed
 * @brief   Timer3 Driver Interface
 *
 * @details
 * This file contains the interface definitions for the Timer3 driver.
 * The driver provides configuration, initialization, control, and runtime
 * services for the Timer3 peripheral of the PIC18F4620 microcontroller.
 *
 * Features:
 *  - Timer and Counter modes
 *  - 16-bit operation
 *  - Prescaler configuration
 *  - Interrupt support with callback mechanism
 *
 * Layer  : MCAL (Microcontroller Abstraction Layer)
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Includes */
      
#include"std_types.h"
#include"hal_gpio.h"
#include"mcal_internal_interrupt.h"

/* Section : Macro Declaration */

// Timer control
#define TIMER3_ENABLE_CFG                    0X01
#define TIMER3_DISABLE_CFG                   0X00

// Timer mode
#define TIMER3_TIMER_MODE_CFG                0X00
#define TIMER3_COUNTER_MODE_CFG              0X01

// Counter sync/async
#define TIMER3_ASYNC_COUNTER_MODE_CFG        0X01
#define TIMER3_SYNC_COUNTER_MODE_CFG         0X00

// Read/Write mode
#define TIMER3_RD_8BIT_MODE_CFG              0X00
#define TIMER3_RD_16BIT_MODE_CFG             0X01

/* Section : Macro Functions Declarations */

// Prescaler configuration
#define TIMER3_PRESCALER_SET(_PRESCALER_)       (T3CONbits.T3CKPS = _PRESCALER_ )

// Timer enable/disable
#define TIMER3_ENABLE()                         (T3CONbits.TMR3ON = TIMER3_ENABLE_CFG)
#define TIMER3_DISABLE()                        (T3CONbits.TMR3ON = TIMER3_DISABLE_CFG)

// Timer / Counter mode select
#define TIMER3_COUNTER_MODE()                   (T3CONbits.TMR3CS = TIMER3_COUNTER_MODE_CFG)
#define TIMER3_TIMER_MODE()                     (T3CONbits.TMR3CS = TIMER3_TIMER_MODE_CFG )

// Counter sync/async
#define TIMER3_SYNC_COUNTER_SET()               (T3CONbits.T3SYNC = TIMER3_SYNC_COUNTER_MODE_CFG)
#define TIMER3_ASYNC_COUNTER_SET()              (T3CONbits.T3SYNC = TIMER3_ASYNC_COUNTER_MODE_CFG)

// Read/Write mode
#define TIMER3_RD_8BIT_MODE_ENABLE()            (T3CONbits.RD16 = TIMER3_RD_8BIT_MODE_CFG)
#define TIMER3_RD_16BIT_MODE_ENABLE()           (T3CONbits.RD16 = TIMER3_RD_16BIT_MODE_CFG)

/* Section : Data Types Declarations */

/**
 * @enum timer3_prescaler_select_t
 * @brief Timer3 prescaler selection options
 *
 * @details
 * These values configure the Timer3 input clock prescaler.
 * They divide the input clock frequency before it increments the timer,
 * allowing for longer timer periods without software intervention.
 */
typedef enum{
    timer3_prescaler_dive_1   = 0 ,
    timer3_prescaler_dive_2   = 1 ,
    timer3_prescaler_dive_4   = 2,        
    timer3_prescaler_dive_8   = 3         
}timer3_prescaler_select_t;


/**
 * @struct timer3_t
 * @brief Timer3 configuration structure
 *
 * @details
 * This structure contains all configuration parameters required to initialize
 * Timer3, including preload value, prescaler, operating mode, and optional
 * interrupt settings.
 */
typedef struct {
    uint16 timer3_preloaded_value; /**< Preload value loaded into TMR3 on initialization
                                       and on overflow for precise periodic timing */

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TMR_InterruptHandler)(void); /**< Pointer to user callback executed in ISR */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority; /**< Interrupt priority configuration (high or low) */
#endif
#endif

    timer3_prescaler_select_t prescaler_division; /**< Input clock prescaler selection */

    uint8 timer3_mode        :1;  /**< Timer3 operating mode
                                       0 = Timer mode (internal clock)
                                       1 = Counter mode (external clock) */

    uint8 timer3_reg_rw_mode :1;  /**< Register read/write mode
                                       0 = 8-bit operation
                                       1 = 16-bit operation */

    uint8 timer3_counter_mode :1; /**< Counter mode synchronization
                                       0 = Synchronous
                                       1 = Asynchronous (external clock) */

    uint8 timer3_reserved     :5; /**< Reserved bits for future use, must be zero */
} timer3_t;


/* Section : Function Declarations */

/* Section : Function Declarations */

/**
 * @brief Initialize Timer3 peripheral using configuration structure
 * @param timer Pointer to Timer3 configuration structure
 * @retval E_OK on success, E_NOT_OK on invalid parameter
 */
Std_ReturnType timer3_init(const timer3_t * timer);

/**
 * @brief Deinitialize Timer3 peripheral
 * @param timer Pointer to Timer3 configuration structure
 * @retval E_OK on success, E_NOT_OK on invalid parameter
 */
Std_ReturnType timer3_Deinit(const timer3_t * timer);

/**
 * @brief Read the current value of Timer3
 * @param timer Pointer to Timer3 configuration structure
 * @param time Pointer to store the read value
 * @retval E_OK on success, E_NOT_OK on invalid parameter
 */
Std_ReturnType timer3_Read_Value(const timer3_t * timer , uint16 * time);

/**
 * @brief Write a value to Timer3 register
 * @param timer Pointer to Timer3 configuration structure
 * @param data Value to write
 * @retval E_OK on success, E_NOT_OK on invalid parameter
 */
Std_ReturnType timer3_Write_Value(const timer3_t * timer , uint16 data);

#endif	/* HAL_TIMER3_H */
