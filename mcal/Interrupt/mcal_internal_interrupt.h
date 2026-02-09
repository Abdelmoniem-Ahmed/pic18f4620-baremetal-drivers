/**
 * @file    mcal_internal_interrupt.h
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   Internal Peripheral Interrupt Driver for PIC MCUs
 * @details This header file provides macros and function prototypes to configure 
 *          and manage internal peripheral interrupts. It supports ADC, timers, CCP,
 *          EUSART, MSSP (SPI/I2C), and I2C bus collision interrupts, with optional 
 *          interrupt priority levels.
 */


#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* Section : Includes */

#include "mcal_interrupt_config.h"
#include"xc.h"
#include "std_types.h"

/* Section : Macro Declaration */


/* Section : Macro Functions Declarations */


/* --------------------- ADC Interrupt --------------------- */
#if    ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THESE Function Will ENABLE INTERRUPT FEATURE FOR ADC */
    #define ADC_INTERRUPT_ENABLE()             (PIE1bits.ADIE = 1)
    /* THESE Function Will DISABLE INTERRUPT FEATURE FOR ADC */
    #define ADC_INTERRUPT_DISABLE()            (PIE1bits.ADIE = 0)
    /* THIS Function Will CLEAR FLAG FOR ADC */   
    #define ADC_INTERRUPT_CLEAR_FLAG()         (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR ADC */
    #define ADC_INTERRUPT_HIGH_PRIORITY()        (IPR1bits.ADIP = 1)
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR ADC */
    #define ADC_INTERRUPT_LOW_PRIORITY()         (IPR1bits.ADIP = 0)
#endif
#endif      /* ADC_INTERRUPT_FEATURE_ENABLE */


/* --------------------- Timer0 Interrupt --------------------- */
#if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THESE Function Will ENABLE INTERRUPT FEATURE FOR TIMER0 */
    #define TIMER0_INTERRUPT_ENABLE()             (INTCONbits.TMR0IE = 1)
    /* THESE Function Will DISABLE INTERRUPT FEATURE FOR TIMER0 */
    #define TIMER0_INTERRUPT_DISABLE()            (INTCONbits.TMR0IE = 0)
    /* THIS Function Will CLEAR FLAG FOR TIMER0 */   
    #define TIMER0_INTERRUPT_CLEAR_FLAG()         (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR TIMER0 */
    #define TIMER0_INTERRUPT_HIGH_PRIORITY()        (INTCON2bits.TMR0IP = 1)
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR TIMER0 */
    #define TIMER0_INTERRUPT_LOW_PRIORITY()         (INTCON2bits.TMR0IP = 0)
#endif
#endif      /* TIMER0_INTERRUPT_FEATURE_ENABLE */

/* --------------------- Timer1 Interrupt --------------------- */
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR TIMER1 */
    #define TIMER1_INTERRUPT_ENABLE()             (PIE1bits.TMR1IE = 1)
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR TIMER1 */
    #define TIMER1_INTERRUPT_DISABLE()            (PIE1bits.TMR1IE = 0)
    /* THIS Function Will CLEAR FLAG FOR TIMER1 */   
    #define TIMER1_INTERRUPT_CLEAR_FLAG()         (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR TIMER1 */
    #define TIMER1_INTERRUPT_HIGH_PRIORITY()        (IPR1bits.TMR1IP = 1)
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR TIMER1 */
    #define TIMER1_INTERRUPT_LOW_PRIORITY()         (IPR1bits.TMR1IP = 0)
#endif
#endif      /* TIMER1_INTERRUPT_FEATURE_ENABLE */

/* --------------------- Timer2 Interrupt --------------------- */
#if  TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR TIMER2 */
    #define TIMER2_INTERRUPT_ENABLE()             (PIE1bits.TMR2IE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR TIMER2 */
    #define TIMER2_INTERRUPT_DISABLE()            (PIE1bits.TMR2IE = 0 )
    /* THIS Function Will CLEAR FLAG FOR TIMER2 */   
    #define TIMER2_INTERRUPT_CLEAR_FLAG()         (PIR1bits.TMR2IF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR TIMER2 */
    #define TIMER2_INTERRUPT_HIGH_PRIORITY()        (IPR1bits.TMR2IP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR TIMER2 */
    #define TIMER2_INTERRUPT_LOW_PRIORITY()         (IPR1bits.TMR2IP = 0 )
#endif
#endif      /* TIMER2_INTERRUPT_FEATURE_ENABLE */

/* --------------------- Timer3 Interrupt --------------------- */
#if  TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR TIMER3 */
    #define TIMER3_INTERRUPT_ENABLE()             (PIE2bits.TMR3IE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR TIMER3 */
    #define TIMER3_INTERRUPT_DISABLE()            (PIE2bits.TMR3IE = 0 )
    /* THIS Function Will CLEAR FLAG FOR TIMER3 */   
    #define TIMER3_INTERRUPT_CLEAR_FLAG()         (PIR2bits.TMR3IF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR TIMER3 */
    #define TIMER3_INTERRUPT_HIGH_PRIORITY()        (IPR2bits.TMR3IP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR TIMER3 */
    #define TIMER3_INTERRUPT_LOW_PRIORITY()         (IPR2bits.TMR3IP = 0 )
#endif
#endif      /* TIMER3_INTERRUPT_FEATURE_ENABLE */

/* --------------------- CCP1 Interrupt --------------------- */
#if  CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR CCP1 */
    #define CCP1_INTERRUPT_ENABLE()             (PIE1bits.CCP1IE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR CCP1 */
    #define CCP1_INTERRUPT_DISABLE()            (PIE1bits.CCP1IE = 0 )
    /* THIS Function Will CLEAR FLAG FOR CCP1 */   
    #define CCP1_INTERRUPT_CLEAR_FLAG()         (PIR1bits.CCP1IF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR CCP1 */
    #define CCP1_INTERRUPT_HIGH_PRIORITY()        (IPR1bits.CCP1IP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR CCP1 */
    #define CCP1_INTERRUPT_LOW_PRIORITY()         (IPR1bits.CCP1IP = 0 )
#endif
#endif      /* CCP1_INTERRUPT_FEATURE_ENABLE */

/* --------------------- CCP2 Interrupt --------------------- */
#if  CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR CCP2 */
    #define CCP2_INTERRUPT_ENABLE()             (PIE2bits.CCP2IE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR CCP2 */
    #define CCP2_INTERRUPT_DISABLE()            (PIE2bits.CCP2IE = 0 )
    /* THIS Function Will CLEAR FLAG FOR CCP2 */   
    #define CCP2_INTERRUPT_CLEAR_FLAG()         (PIR2bits.CCP2IF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR CCP2 */
    #define CCP2_INTERRUPT_HIGH_PRIORITY()        (IPR2bits.CCP2IP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR CCP2*/
    #define CCP2INTERRUPT_LOW_PRIORITY()         (IPR2bits.CCP2IP = 0 )
#endif
#endif      /* CCP2_INTERRUPT_FEATURE_ENABLE */

/* --------------------- EUSART TX/RX Interrupts --------------------- */
#if  EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR EUSART TX */
    #define EUSART_TX_INTERRUPT_ENABLE()             (PIE1bits.TXIE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR EUSART_TX */
    #define EUSART_TX_INTERRUPT_DISABLE()            (PIE1bits.TXIE = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR EUSART_TX */
    #define EUSART_TX_INTERRUPT_HIGH_PRIORITY()        (IPR1bits.TXIP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR EUSART_TX*/
    #define EUSART_TX_INTERRUPT_LOW_PRIORITY()         (IPR1bits.TXIP = 0 )
#endif
#endif      /* EUSART_TX_INTERRUPT_FEATURE_ENABLE */

#if  EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR EUSART_RX */
    #define EUSART_RX_INTERRUPT_ENABLE()             (PIE1bits.RCIE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR EUSART_RX */
    #define EUSART_RX_INTERRUPT_DISABLE()            (PIE1bits.RCIE = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR EUSART_RX */
    #define EUSART_RX_INTERRUPT_HIGH_PRIORITY()        (IPR1bits.RCIP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR EUSART_RX*/
    #define EUSART_RX_INTERRUPT_LOW_PRIORITY()         (IPR1bits.RCIP = 0 )
#endif
#endif      /* EUSART_RX_INTERRUPT_FEATURE_ENABLE */

/* --------------------- MSSP SPI/I2C Interrupts --------------------- */
#if  INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE 
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR SPI */
    #define MSSP_SPI_INTERRUPT_ENABLE()             ( PIE1bits.SSPIE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR EUSART_RX */
    #define MSSP_SPI_INTERRUPT_DISABLE()            ( PIE1bits.SSPIE = 0 )
    /* THIS Function Will CLEAR FLAG FOR SPI */   
    #define MSSP_SPI_INTERRUPT_CLEAR_FLAG()         ( PIR1bits.SSPIF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR EUSART_RX */
    #define MSSP_SPI_INTERRUPT_HIGH_PRIORITY()      ( IPR1bits.SSPIP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR EUSART_RX*/
    #define MSSP_SPI_INTERRUPT_LOW_PRIORITY()       ( IPR1bits.SSPIP = 0 )
#endif
#endif      /* MSSP_SPI_INTERRUPT_FEATURE_ENABLE */

#if  INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE 
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR I2C */
    #define MSSP_I2C_INTERRUPT_ENABLE()             ( PIE1bits.SSPIE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR I2C */
    #define MSSP_I2C_INTERRUPT_DISABLE()            ( PIE1bits.SSPIE = 0 )
    /* THIS Function Will CLEAR FLAG FOR I2C */   
    #define MSSP_I2C_INTERRUPT_CLEAR_FLAG()         ( PIR1bits.SSPIF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR I2C */
    #define MSSP_I2C_INTERRUPT_HIGH_PRIORITY()      ( IPR1bits.SSPIP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR I2C*/
    #define MSSP_I2C_INTERRUPT_LOW_PRIORITY()       ( IPR1bits.SSPIP = 0 )
#endif
#endif      /* MSSP_I2C_INTERRUPT_FEATURE_ENABLE */

#if  INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE 
    /* THIS Function Will ENABLE INTERRUPT FEATURE FOR I2C Bus Collision */
    #define MSSP_I2C_BUS_COLL_INTERRUPT_ENABLE()        (PIE2bits.BCLIE = 1 )
    /* THIS Function Will DISABLE INTERRUPT FEATURE FOR I2C */
    #define MSSP_I2C_BUS_COLL_INTERRUPT_DISABLE()       (PIE2bits.BCLIE = 0 )
    /* THIS Function Will CLEAR FLAG FOR I2C */   
    #define MSSP_I2C_BUS_COLL_INTERRUPT_CLEAR_FLAG()    (PIR2bits.BCLIF = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    /* THIS Function Will SET INTERRUPT PRIORITY HIGH FOR I2C */
    #define MSSP_I2C_BUS_COLL_INTERRUPT_HIGH_PRIORITY() (IPR2bits.BCLIP = 1 )
    /* THIS Function Will SET INTERRUPT PRIORITY LOW FOR I2C*/
    #define MSSP_I2C_BUS_COLL_INTERRUPT_LOW_PRIORITY()  (IPR2bits.BCLIP = 0 )
#endif
#endif

/* Section : Data Types Declarations */


/* Section : Function Declarations */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

