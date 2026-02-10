/**
 * @file    mcal_interrupt_manager.c
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/Abdelmoniem-Ahmed/
 * @brief   Global Interrupt Manager Implementation
 * @details
 * This file implements the central interrupt dispatcher for the PIC MCU.
 *
 * Responsibilities:
 * - Acts as the single entry point for all hardware interrupts
 * - Checks interrupt enable bits and interrupt flags
 * - Dispatches execution to the corresponding peripheral ISR
 *
 * Supported Interrupt Sources:
 * - External interrupts (INT0, INT1, INT2)
 * - PORTB change interrupts (RB4?RB7)
 * - ADC
 * - Timers (TMR0, TMR1, TMR2, TMR3)
 * - CCP modules (CCP1, CCP2)
 * - EUSART (TX, RX)
 * - MSSP (SPI, I2C, I2C Bus Collision)
 *
 * Notes:
 * - This module does NOT contain application logic
 * - All peripheral-specific logic is handled inside their own drivers
 * - ISR functions called here are lightweight and callback-based
 */

/* ----------------------------------------------------
 * Section : Includes
 * ----------------------------------------------------
 */

#include "mcal_interrupt_manager.h"

/* ----------------------------------------------------
 * Section : Static Flags for RBx Change Detection
 * ----------------------------------------------------
 * These flags are used to detect rising and falling
 * edges manually for PORTB change interrupts.
 */
uint8 RB4_ISR_Flag = 1 , RB5_ISR_Flag = 1 , RB6_ISR_Flag = 1 , RB7_ISR_Flag = 1;

/* ----------------------------------------------------
 * Section : Interrupt Manager with Priority Levels
 * ----------------------------------------------------
 */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_PRIORITY_ENABLE

/**
 * @brief High Priority Interrupt Service Routine
 */
void __interrupt(high_priority) Interrupt_ManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE ) && (INTERRUPT_OCCUR == INTCONbits.INT0IF ) ){
        INT0_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF ) ){
        INT2_ISR();  
    }
    else{ /* Nothing */ }
}

/**
 * @brief Low Priority Interrupt Service Routine
 */
void __interrupt(low_priority) Interrupt_Managerlow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF ) ){
        INT1_ISR();
    }
    else{ /* Nothing */ }
}

#else

/* ----------------------------------------------------
 * Section : Interrupt Manager without Priority Levels
 * ----------------------------------------------------
 */


/**
 * @brief Global Interrupt Service Routine (No Priority Mode)
 */
void __interrupt() Interrupt_Manager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE ) && (INTERRUPT_OCCUR == INTCONbits.INT0IF ) ){
        INT0_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF ) ){
        INT1_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF ) ){
        INT2_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       ( 1 == PORTBbits.RB4) && (1 == RB4_ISR_Flag) ){
        RB4_ISR_Flag = 0;
        RB4_ISR(1);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       ( 0 == PORTBbits.RB4)&& (0 == RB4_ISR_Flag)  ){
        RB4_ISR_Flag = 1;
        RB4_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       ( 1 == PORTBbits.RB5)&& (1 == RB5_ISR_Flag) ){
        RB5_ISR_Flag = 0;
        RB5_ISR(1);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       ( 0 == PORTBbits.RB5) && (0 == RB5_ISR_Flag) ){
        RB5_ISR_Flag = 1;
        RB5_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       ( 1 == PORTBbits.RB6)&& (1 == RB6_ISR_Flag) ){
        RB6_ISR_Flag = 0;
        RB6_ISR(1);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       (0 == PORTBbits.RB6) && (0 == RB6_ISR_Flag) ){
        RB6_ISR_Flag = 1 ;
        RB6_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       (1 == PORTBbits.RB7) && (1 == RB7_ISR_Flag)){
        RB7_ISR_Flag = 0;
        RB7_ISR(1);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) && 
       (0 == PORTBbits.RB7) && (0 == RB7_ISR_Flag) ){
        RB7_ISR_Flag = 1;
        RB7_ISR(0);
    }
    else{ /* Nothing */ }   
/*---------- until implemented will be commented ----------*/
    
#if    INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE    
    if((INTERRUPT_ENABLE == PIE1bits.ADIE ) && (INTERRUPT_OCCUR == PIR1bits.ADIF )){
        ADC_ISR();
    }
    else{ /* Nothing */ }
#endif    
    
//#if    TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
//        TMR0_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//
//#if    TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
//        TMR1_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//
//#if    TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
//        TMR2_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//
//#if    TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
//        TMR3_ISR();
//    }
//    else{ /* Nothing */ }
//#endif    
//
//#if    CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
//        CCP1_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//    
//#if    CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
//        CCP2_ISR();
//    }
//    else{ /* Nothing */ }
//#endif    
//
//#if    EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF)){
//        EUSART_TX_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//    
//#if    EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF)){
//        EUSART_RX_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//
//#if    MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
//        MSSP_SPI_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//
//#if    MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
//        MSSP_I2C_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
//
//#if    MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
//    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF)){
//        MSSP_I2C_BC_ISR();
//    }
//    else{ /* Nothing */ }
//#endif
}
#endif