/**
 * @file    Timer1.c
 * @author  Abdelmoniem Ahmed
 * @brief   Timer1 Driver Implementation
 *
 * @details
 * This file implements the Timer1 driver functions for PIC18F4620.
 * Supports Timer/Counter mode, 16-bit operation, prescaler, preload,
 * reload, and optional interrupt callback mechanism.
 *
 * Layer  : MCAL
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#include "timer1.h"

/* Section : Private (Static) Variables */

/** 
 * @brief Preload value for Timer1.
 * Used to reload the timer on overflow for precise periodic timing.
 */
static uint16 timer1_preload = ZERO_INIT;

/**
 * @brief Pointer to user-defined Timer1 overflow callback.
 * Assigned during initialization and executed inside ISR.
 */
#if   TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (* TMR1_InterruptHandler ) (void) = NULL;
#endif

/* Section : Private (Static) Functions */
    
    
/**
 * @brief Configure Timer1 mode as Timer or Counter.
 * @details Sets Timer1 operating mode, counter sync/async, and oscillator
 *          based on the provided configuration structure.
 * @param timer: Pointer to Timer1 configuration structure
 */    
static void timer1_Timer_OR_Counter_Mode_Set(const timer1_t * timer);


/* Section : Function Definitions */
    
/**
 * @brief Initialize Timer1 with the given configuration
 * @param timer: Pointer to configuration structure
 * @retval E_OK on success, E_NOT_OK on invalid parameters
 */
Std_ReturnType timer1_init(const timer1_t * timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        TIMER1_PRESCALER_SELECT(timer->prescaler_division);
        timer1_Timer_OR_Counter_Mode_Set(timer);
        TIMER1_RD_16BIT_MODE_ENABLE();
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TMR1_InterruptHandler = timer->TMR_InterruptHandler ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        if(Interrupt_High_Priority == timer->priority){
            TIMER1_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{
            TIMER1_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        INTERRUPT_PriorityFeatureEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        TIMER1_INTERRUPT_ENABLE();
#endif     
        timer1_preload = timer->timer1_preload_value ;
        TMR1H = ((uint8)(timer->timer1_preload_value >> 8)) ;
        TMR1L = ((uint8)(timer->timer1_preload_value)) ;
        TIMER1_ENABLE();
    }
    return ret;
}

Std_ReturnType timer1_Deinit(const timer1_t * timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

Std_ReturnType timer1_Read_Value(const timer1_t * timer , uint16 * time){
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
    return ret;
}

Std_ReturnType timer1_Write_Value(const timer1_t * timer , uint16 data){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = ((uint8)(data >> 8)) ;
        TMR1L = ((uint8)(data)) ;
    }
    return ret;
}



static void timer1_Timer_OR_Counter_Mode_Set(const timer1_t * timer){
    if( TIMER1_TIMER_MODE_CFG == timer->timer1_mode){
        TIMER1_TIMER_MODE();
    }
    else{
        TIMER1_COUNTER_MODE();
        if(TIMER1_SYNC_COUNTER_MODE_CFG == timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_SET();
        }
        else{
            TIMER1_ASYNC_COUNTER_SET();
        }
    }
    if(TIMER1_OSC_ENABLE == timer->timer1_osc_cfg){
            TIMER1_OSC_MODE_ENABLE();
        }
        else{
            TIMER1_OSC_MODE_DISABLE();
        }
}


/**
 * @brief Timer1 Overflow ISR
 * @details Clears the interrupt flag, reloads the preload value,
 *          and executes the user callback if assigned.
 */
void TMR1_ISR(void){
    TIMER1_INTERRUPT_CLEAR_FLAG();
    if(TMR1_InterruptHandler){
        TMR1_InterruptHandler();
    }
    TMR1H = ((uint8)(timer1_preload >> 8)) ;
    TMR1L = ((uint8)(timer1_preload)) ;
}
