/**
 * @file    mcal_externl_interrupt.h
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   External Interrupt Driver for PIC MCUs
 * @details This header file provides macros, data types, and function 
 *          prototypes to configure and manage external interrupts.
 *          Supports INT0, INT1, INT2, and PORTB change interrupts (RB4-RB7)
 *          with callback mechanism and optional interrupt priority levels.
 */

#ifndef MCAL_EXTERNL_INTERRUPT_H
#define	MCAL_EXTERNL_INTERRUPT_H

/* Section : Includes */


#include "mcal_interrupt_config.h"

/* Section : Macro Declaration */



/* Section : Macro Functions Declarations */



#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* INT0 FUNCTIONS "ENABLE - SET EDGE - CLEAR FLAG" */

/* THESE Function Will EN/DISABLE INTERRUPT FEATURE FOR INT0 */
#define EXTERNAL_INTERRUPT_INT0_ENABLE()             (INTCONbits.INT0IE = 1)
#define EXTERNAL_INTERRUPT_INT0_DISABLE()            (INTCONbits.INT0IE = 0)
/* THIS Function Will CLEAR FLAG FOR INT0 */
#define EXTERNAL_INTERRUPT_INT0_CLEAR_FLAG()         (INTCONbits.INT0IF = 0)
/* THESE Function Will SET EDGE TRIGERRING RISING/FALLING FOR INT0 */
#define EXTERNAL_INTERRUPT_INT0_SET_RISING_EDGE()    (INTCON2bits.INTEDG0 = 1)
#define EXTERNAL_INTERRUPT_INT0_SET_FALLING_EDGE()   (INTCON2bits.INTEDG0 = 0)

/* INT1 FUNCTIONS "ENABLE - SET EDGE - CLEAR FLAG " */

/* THESE Function Will EN/DISABLE INTERRUPT FEATURE FOR INT1 */
#define EXTERNAL_INTERRUPT_INT1_ENABLE()             (INTCON3bits.INT1IE = 1)
#define EXTERNAL_INTERRUPT_INT1_DISABLE()            (INTCON3bits.INT1IE = 0)
/* THESE Function Will SET EDGE TRIGERRING RISING/FALLING FOR INT1 */
#define EXTERNAL_INTERRUPT_INT1_SET_RISING_EDGE()    (INTCON2bits.INTEDG1 = 1)
#define EXTERNAL_INTERRUPT_INT1_SET_FALLING_EDGE()   (INTCON2bits.INTEDG1 = 0)
/* THIS Function Will CLEAR FLAG FOR INT1 */
#define EXTERNAL_INTERRUPT_INT1_CLEAR_FLAG()         (INTCON3bits.INT1IF  = 0)

/* INT2 FUNCTIONS "ENABLE - SET EDGE - CLEAR FLAG " */

/* THESE Function Will EN/DISABLE INTERRUPT FEATURE FOR INT2 */
#define EXTERNAL_INTERRUPT_INT2_ENABLE()             (INTCON3bits.INT2IE = 1)
#define EXTERNAL_INTERRUPT_INT2_DISABLE()            (INTCON3bits.INT2IE = 0)
/* THESE Function Will SET EDGE TRIGERRING RISING/FALLING FOR INT2 */
#define EXTERNAL_INTERRUPT_INT2_SET_RISING_EDGE()    (INTCON2bits.INTEDG2 = 1)
#define EXTERNAL_INTERRUPT_INT2_SET_FALLING_EDGE()   (INTCON2bits.INTEDG2 = 0)
/* THIS Function Will CLEAR FLAG FOR INT2 */
#define EXTERNAL_INTERRUPT_INT2_CLEAR_FLAG()         (INTCON3bits.INT2IF  = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

    /* THESE Function Will SET INTERRUPT PRIORITY HIGH/LOW FOR INT1 */
    #define EXTERNAL_INTERRUPT_INT1_HIGH_PRIORITY()        (INTCON3bits.INT1IP = 1)
    #define EXTERNAL_INTERRUPT_INT1_LOW_PRIORITY()         (INTCON3bits.INT1IP = 0)

    /* THESE Function Will SET INTERRUPT PRIORITY HIGH/LOW FOR INT2 */
    #define EXTERNAL_INTERRUPT_INT2_HIGH_PRIORITY()        (INTCON3bits.INT2IP = 1)
    #define EXTERNAL_INTERRUPT_INT2_LOW_PRIORITY()         (INTCON3bits.INT2IP = 0)

#endif 

#endif


/**************** ON CHANGE INTERRUPTS ****************/


#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* THESE Function Will EN/DISABLE INTERRUPT FEATURE FOR RBx */
#define EXTERNAL_INTERRUPTS_RBx_ENABLE()            (INTCONbits.RBIE = 1)    
#define EXTERNAL_INTERRUPTS_RBx_DISABLE()           (INTCONbits.RBIE = 0)
/* THIS Function Will CLEAR FLAG FOR RBx */
#define EXTERNAL_INTERRUPTS_RBx_CLEAR_FLAG()        (INTCONbits.RBIF = 0)

    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

    /* THESE Function Will SET INTERRUPT PRIORITY HIGH/LOW FOR INT1 */
    #define EXTERNAL_INTERRUPT_RBx_HIGH_PRIORITY()        (INTCON2bits.RBIP = 1)
    #define EXTERNAL_INTERRUPT_RBx_LOW_PRIORITY()         (INTCON2bits.RBIP = 0)

    #endif

#endif


/* Section : Data Types Declarations */

/**
 * @brief INTx sources enumeration
 * @details Defines external interrupt sources for INT0, INT1, and INT2
 */
typedef enum{
    Interrupt_INT0 ,
    Interrupt_INT1 ,
    Interrupt_INT2         
}INTERRUPT_INTx_src;

/**
 * @brief Edge detection types
 * @details Determines if the interrupt triggers on rising or falling edge
 */
typedef enum{
    Interrupt_Falling_Edge = 0 ,
    Interrupt_Rising_Edge        
}INTERRUPT_INTx_EDGE_t;

/**
 * @brief INTx interrupt configuration structure
 * @details Used to initialize INT0, INT1, or INT2 with callback, pin, priority, and edge
 */
typedef struct {
    void (* External_InterruptHandler ) (void) ;
    INTERRUPT_INTx_src source ;
    INTERRUPT_Priority_cfg priority;
    INTERRUPT_INTx_EDGE_t edge ;
    pin_config_t  mcu_pin ;
}Interrupt_INTx_t;

/**
 * @brief RBx interrupt configuration structure
 * @details Used to initialize RB4-RB7 change interrupts with callbacks for high/low edges
 */
typedef struct {
    void (* External_InterruptHandler_High ) (void) ;
    void (* External_InterruptHandler_Low ) (void) ;
    pin_config_t  mcu_pin ;
    INTERRUPT_Priority_cfg priority;
}Interrupt_RBx_t;

/* Section : Function Declarations */

/**
 * @brief Initialize INTx interrupt
 * @param interrupt_obj Pointer to INTx configuration structure
 * @return Std_ReturnType E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType interrupt_INTx_Init(const Interrupt_INTx_t * interrupt_obj);

/**
 * @brief De-initialize INTx interrupt
 * @param interrupt_obj Pointer to INTx configuration structure
 * @return Std_ReturnType E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType interrupt_INTx_DeInit(const Interrupt_INTx_t * interrupt_obj);

/**
 * @brief Initialize RBx change interrupt
 * @param interrupt_obj Pointer to RBx configuration structure
 * @return Std_ReturnType E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType interrupt_RBx_Init(const Interrupt_RBx_t * interrupt_obj);

/**
 * @brief De-initialize RBx change interrupt
 * @param interrupt_obj Pointer to RBx configuration structure
 * @return Std_ReturnType E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType interrupt_RBx_DeInit(const Interrupt_RBx_t * interrupt_obj);

#endif	/* MCAL_EXTERNL_INTERRUPT_H */

