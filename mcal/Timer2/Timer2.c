/**
 * @file    hal_timer2.c
 * @author  Abdelmoniem Ahmed
 * @brief   Timer2 Driver Implementation for PIC18F4620
 *
 * @details
 * This file implements the Timer2 driver functions.
 * It supports:
 *  - 8-bit Timer operation
 *  - Configurable prescaler and postscaler
 *  - Preload and automatic reload on overflow
 *  - Optional interrupt callback mechanism
 *  - Optional interrupt priority handling
 *
 * Layer  : MCAL
 * Target : PIC18F4620
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#include"Timer2.h"

/* Section : Private (Static) Variables */

/**
 * @brief Preload value for Timer2
 * @details Reloaded automatically on overflow for periodic timing
 */
static uint8 timer2_preloaded = ZERO_INIT;

/**
 * @brief Pointer to user-defined Timer2 overflow callback
 * @details Assigned during initialization and executed inside ISR
 */
#if   TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (* TMR2_InterruptHandler ) (void) = NULL;
#endif

/* Section : Function Definitions */
    
Std_ReturnType timer2_init(const timer2_t * timer){
    Std_ReturnType ret = E_OK ;
    if(NULL == timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER2_DISABLE();
        
        TMR2 = timer->preloaded_value ;
        timer2_preloaded = timer->preloaded_value ;
        
        T2CONbits.T2CKPS = timer->prescaler_division  ;
        T2CONbits.TOUTPS = timer->postscaler_division ;
        
#if   TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER2_INTERRUPT_CLEAR_FLAG();
            TMR2_InterruptHandler = timer->TMR_InterruptHandler ;
#if   INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
            if(Interrupt_High_Priority == timer->priority){
                TIMER2_INTERRUPT_HIGH_PRIORITY();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else{
                TIMER2_INTERRUPT_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowEnable();
            }
                INTERRUPT_PriorityFeatureEnable();
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();        
#endif
            TIMER2_INTERRUPT_ENABLE();
#endif 
            TIMER2_ENABLE();
    }
    return ret;
}

Std_ReturnType timer2_Deinit(const timer2_t * timer){
    Std_ReturnType ret = E_OK ;
    if(NULL == timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER2_DISABLE();
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif        
    }
    return ret;
}

Std_ReturnType timer2_Read_Value(const timer2_t * timer , uint8 * time){
    Std_ReturnType ret = E_OK;
    if((NULL == timer) || (NULL == time)){
        ret = E_NOT_OK;
    }
    else{
        *time = TMR2 ;
    }
    return ret;
}

Std_ReturnType timer2_Write_Value(const timer2_t * timer , uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = data ;
    }
    return ret;
}


/**
 * @brief Timer2 Overflow Interrupt Service Routine
 *
 * @details
 * Called automatically on Timer2 overflow. Performs the following:
 *  - Clears Timer2 interrupt flag
 *  - Executes user-defined callback (if assigned)
 *  - Reloads Timer2 with the preloaded value to maintain precise timing
 */

void TMR2_ISR(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
    TMR2 = timer2_preloaded ;
}

