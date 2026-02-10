/**
 * @file    Timer0.c
 * @author  Abdelmoniem Ahmed
 * @brief   Timer0 Driver Source File
 *
 * @details
 * This file contains the implementation of the Timer0 driver APIs.
 * It handles initialization, runtime services, and interrupt processing
 * for the Timer0 peripheral.
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#include "Timer0.h"

/* ===================== Static Variables ===================== */

static uint16 timer0_preload = ZERO_INIT;
static uint8 timer0_resolution = ZERO_INIT;

#if   TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (* TMR0_InterruptHandler ) (void) = NULL;
#endif

/* ===================== Static Helper Functions ===================== */

/**
 * @brief Configure Timer0 prescaler
 */
static void timer0_prescaler_config(const timer0_t * timer);

/**
 * @brief Select Timer or Counter mode
 */
static void timer0_Timer_OR_Counter_Mode_Set(const timer0_t * timer);

/**
 * @brief Configure Timer0 register size (8-bit / 16-bit)
 */
static void timer0_register_size_set(const timer0_t * timer);



/* ===================== Function Definitions ===================== */


/**
 * @brief Initialize Timer0 module
 */
Std_ReturnType timer0_init(const timer0_t * timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        timer0_prescaler_config(timer);
        timer0_Timer_OR_Counter_Mode_Set(timer);
        timer0_register_size_set(timer);
        timer0_resolution = timer->timer_resolution;
        if(TIMER0_16BIT_MODE_CFG == timer->timer_resolution){
            TMR0H = ((uint8)(timer->timer0_preload_value >> 8)) ;
        }
        TMR0L = ((uint8)(timer->timer0_preload_value)) ;
#if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_CLEAR_FLAG();
        TMR0_InterruptHandler = timer->TMR_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        if(Interrupt_High_Priority == timer->priority){
            TIMER0_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{
            TIMER0_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        INTERRUPT_PriorityFeatureEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif     
        TIMER0_INTERRUPT_ENABLE();
#endif   
        TIMER0_ENABLE();
        timer0_preload = timer->timer0_preload_value ;
    }
    return ret;
}

/**
 * @brief Deinitialize Timer0 module
 */
Std_ReturnType timer0_Deinit(void){

    Std_ReturnType ret = E_OK;    
    TIMER0_DISABLE();
#if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_DISABLE();
#endif
    return ret;
}


/**
 * @brief Read Timer0 current value
 */
Std_ReturnType timer0_Read_Value(const timer0_t * timer , uint16 * time){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0l = ZERO_INIT , l_tmr0h = ZERO_INIT ;
    if((NULL == timer) || (NULL == time)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *time = ( (uint16) ( (l_tmr0h << 8) + l_tmr0l ) );
    }
    return ret;
}


/**
 * @brief Write value to Timer0 register
 */
Std_ReturnType timer0_Write_Value(const timer0_t * timer , uint16 data){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        if(TIMER0_16BIT_MODE_CFG == timer->timer_resolution){
            TMR0H = ((uint8)(data >> 8)) ;
        }
        TMR0L = ((uint8)(data)) ;
    }
    return ret;
}


/**
 * @brief Timer0 Interrupt Service Routine
 */
void TMR0_ISR (void){
    TIMER0_INTERRUPT_CLEAR_FLAG();
    if( TIMER0_16BIT_MODE_CFG == timer0_resolution){
        TMR0H = ((uint8)(timer0_preload >> 8)) ;
    }
    TMR0L = ((uint8)(timer0_preload)) ;
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}

/* ===================== Static Function Definitions ===================== */


static void timer0_prescaler_config(const timer0_t * timer){
    if(PRESCALER_ASSIGNED_CFG == timer->prescaler_enable){
        PRESCALER_ASSIGNED();
        T0CONbits.T0PS = timer->prescaler_division;
    }
    else{
        PRESCALER_NOT_ASSIGNED();
    }
}

static void timer0_Timer_OR_Counter_Mode_Set(const timer0_t * timer){
    if( TIMER0_INTERNAL_CLK_SRC_CFG == timer->clock_source){
        TIMER0_TIMER_MODE();
    }
    else{
        TIMER0_COUNTER_MODE();
        if(TIMER0_RISING_EDGE_CFG == timer->counter_edge_select){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else{
            TIMER0_FALLING_EDGE_ENABLE();
        }
    }
}


static void timer0_register_size_set(const timer0_t * timer){
    if(TIMER0_8BIT_MODE_CFG == timer->timer_resolution){
        TIMER0_8BIT_Register_MODE_ENABLE();
    }
    else{
        TIMER0_16BIT_Register_MODE_ENABLE();
    }
}

