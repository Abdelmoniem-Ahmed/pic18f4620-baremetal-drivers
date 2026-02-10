/**
 * @file    Timer3.c
 * @author  Abdelmoniem Ahmed
 * @brief   Timer3 Driver Implementation
 *
 * @details
 * This file implements the Timer3 driver functions for the PIC18F4620.
 * The driver supports Timer/Counter mode, 16-bit operation, prescaler,
 * preload, reload, and optional interrupt callback mechanism.
 *
 * Layer  : MCAL (Microcontroller Abstraction Layer)
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#include "Timer3.h"

/* Section : Private (Static) Variables */

/**
 * @brief Preload value for Timer3.
 * @details Used to reload Timer3 on overflow to achieve precise periodic timing.
 */
static uint16 timer3_preload = ZERO_INIT;

/**
 * @brief Pointer to user-defined Timer3 overflow callback function.
 * @details Assigned during initialization; called inside the ISR when
 *          Timer3 overflows.
 */
#if   TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (* TMR3_InterruptHandler ) (void) = NULL;
#endif

        /* Section : Private (Static) Functions */
    
/**
 * @brief Configure Timer3 as Timer or Counter.
 * @details Sets the operating mode, counter sync/async, and prescaler
 *          according to the user configuration structure.
 * @param timer Pointer to Timer3 configuration structure
 */    
static void timer3_Timer_OR_Counter_Mode_Set(const timer3_t * timer);    

        /* Section : Function Definitions */

/**
 * @brief Initialize Timer3 with the provided configuration
 * @param timer Pointer to configuration structure
 * @retval E_OK on successful initialization
 * @retval E_NOT_OK if input pointer is NULL
 */
Std_ReturnType timer3_init(const timer3_t * timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        TIMER3_PRESCALER_SET(timer->prescaler_division);
        timer3_Timer_OR_Counter_Mode_Set(timer);
        TIMER3_RD_16BIT_MODE_ENABLE();
#if  TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TMR3_InterruptHandler = timer->TMR_InterruptHandler ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        if(Interrupt_High_Priority == timer->priority){
            TIMER3_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{
            TIMER3_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        INTERRUPT_PriorityFeatureEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        TIMER3_INTERRUPT_ENABLE();
#endif        
        timer3_preload = timer->timer3_preloaded_value;
        TMR3H = ((uint8)(timer->timer3_preloaded_value >> 8)) ;
        TMR3L = ((uint8)(timer->timer3_preloaded_value)) ;
        
        TIMER3_ENABLE();
    }
    return ret ;
}

/**
 * @brief Deinitialize Timer3 and optionally disable its interrupt
 * @param timer Pointer to configuration structure
 * @retval E_OK on success
 * @retval E_NOT_OK if input pointer is NULL
 */
Std_ReturnType timer3_Deinit(const timer3_t * timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
#if  TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif
    }
    return ret ;
}

/**
 * @brief Read the current value of Timer3
 * @param timer Pointer to configuration structure
 * @param time Pointer to store the read value
 * @retval E_OK on success
 * @retval E_NOT_OK if input pointers are NULL
 */
Std_ReturnType timer3_Read_Value(const timer3_t * timer , uint16 * time){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr1l = ZERO_INIT , l_tmr1h = ZERO_INIT ;    
    if((NULL == timer) || (NULL == time)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *time = ( (uint16) ( (l_tmr1h << 8) + l_tmr1l ) );
    }
    return ret ;
}

/**
 * @brief Write a value to Timer3 register
 * @param timer Pointer to configuration structure
 * @param data 16-bit value to load into Timer3
 * @retval E_OK on success
 * @retval E_NOT_OK if input pointer is NULL
 */
Std_ReturnType timer3_Write_Value(const timer3_t * timer , uint16 data){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = ((uint8)(data >> 8 )) ;
        TMR3L = ((uint8)(data));
    }
    return ret ;
}

/**
 * @brief Configure Timer3 Timer/Counter mode
 * @param timer Pointer to Timer3 configuration structure
 * @details Sets Timer or Counter mode and selects synchronous/asynchronous
 *          operation for Counter mode.
 */
static void timer3_Timer_OR_Counter_Mode_Set(const timer3_t * timer){
    if( TIMER3_TIMER_MODE_CFG == timer->timer3_mode){
        TIMER3_TIMER_MODE();
    }
    else{
        TIMER3_COUNTER_MODE();
        if(TIMER3_SYNC_COUNTER_MODE_CFG == timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_SET();
        }
        else{
            TIMER3_ASYNC_COUNTER_SET();
        }
    }
}


/**
 * @brief Timer3 overflow ISR
 * @details Clears the interrupt flag, executes user callback if defined,
 *          and reloads the Timer3 preload value.
 */
void TMR3_ISR(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    if(TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
    TMR3H = ((uint8)(timer3_preload >> 8 )) ;
    TMR3L = ((uint8)(timer3_preload));
}
