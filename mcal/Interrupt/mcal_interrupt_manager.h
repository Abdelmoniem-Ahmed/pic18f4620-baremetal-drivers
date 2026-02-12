/**
 * @file    mcal_interrupt_manager.h
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   MCAL Interrupt Manager Interface
 * @details This file declares all Interrupt Service Routine (ISR) interfaces
 *          used by the MCAL interrupt management module.
 *
 *          The interrupt manager is responsible for:
 *          - Dispatching hardware interrupt events
 *          - Calling the appropriate peripheral ISR
 *          - Supporting both priority and non-priority interrupt modes
 *
 *          This file only contains ISR prototypes.
 *          ISR implementations are provided in mcal_interrupt_manager.c.
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section : Includes */

#include "mcal_interrupt_config.h"

/* Section : Macro Declaration */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/* Section : Function Declarations */

/* ----------------------------------------------------
 * Section : External Interrupt ISR Prototypes
 * ----------------------------------------------------
 */

/**
 * @brief ISR for External Interrupt INT0
 * @note  Clears interrupt flag and calls registered callback (if available)
 */
void INT0_ISR(void);

/**
 * @brief ISR for External Interrupt INT1
 * @note  Clears interrupt flag and calls registered callback (if available)
 */
void INT1_ISR(void);

/**
 * @brief ISR for External Interrupt INT2
 * @note  Clears interrupt flag and calls registered callback (if available)
 */
void INT2_ISR(void);

/**
 * @brief ISR for PORTB change interrupt on RB4
 * @param source Indicates logic level (1 = High, 0 = Low)
 */
void RB4_ISR(uint8 source);

/**
 * @brief ISR for PORTB change interrupt on RB5
 * @param source Indicates logic level (1 = High, 0 = Low)
 */
void RB5_ISR(uint8 source);

/**
 * @brief ISR for PORTB change interrupt on RB6
 * @param source Indicates logic level (1 = High, 0 = Low)
 */
void RB6_ISR(uint8 source);

/**
 * @brief ISR for PORTB change interrupt on RB7
 * @param source Indicates logic level (1 = High, 0 = Low)
 */
void RB7_ISR(uint8 source);

/* ----------------------------------------------------
 * Section : Internal Peripheral Interrupt ISR Prototypes
 * ----------------------------------------------------
 */

/**
 * @brief ISR for Analog-to-Digital Converter (ADC)
 */
void ADC_ISR(void);

/**
 * @brief ISR for Timer0 overflow interrupt
 */
void TMR0_ISR(void);

/**
 * @brief ISR for Timer1 overflow interrupt
 */
void TMR1_ISR(void);

/**
 * @brief ISR for Timer2 overflow interrupt
 */
void TMR2_ISR(void);

/**
 * @brief ISR for Timer3 overflow interrupt
 */
void TMR3_ISR(void);

/**
 * @brief ISR for Capture/Compare/PWM module CCP1
 */
void CCP1_ISR(void);

/**
 * @brief ISR for Capture/Compare/PWM module CCP2
 */
void CCP2_ISR(void);

/**
 * @brief ISR for EUSART transmit interrupt
 */
void EUSART_TX_ISR(void);

/**
 * @brief ISR for EUSART receive interrupt
 */
void EUSART_RX_ISR(void);

///**
// * @brief ISR for MSSP SPI interrupt
// */
//void MSSP_SPI_ISR(void);
//
///**
// * @brief ISR for MSSP I2C interrupt
// */
//void MSSP_I2C_ISR(void);
//
///**
// * @brief ISR for MSSP I2C bus collision interrupt
// */
//void MSSP_I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

