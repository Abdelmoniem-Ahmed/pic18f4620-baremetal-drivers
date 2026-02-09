/**
 * @file    mcal_interrupt_gen_cfg.h
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   Global Interrupt Configuration File
 * @details This file controls the compile-time enabling and disabling of
 *          interrupt features across the MCAL layer.
 *          Each macro acts as a feature switch to include or exclude
 *          interrupt-related code for specific peripherals.
 *
 *          This configuration file is intended to be modified by the user
 *          based on project requirements.
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* ----------------------------------------------------
 * Global Interrupt Feature Control
 * ----------------------------------------------------
 */

/**
 * @brief Enable value for interrupt features
 */
#define INTERRUPT_FEATURE_ENABLE            0x01

/**
 * @brief Disable value for interrupt features
 */
#define INTERRUPT_FEATURE_DISABLE           0x00

/* ----------------------------------------------------
 * Interrupt Priority Configuration
 * ----------------------------------------------------
 * Uncomment the following macro to enable interrupt
 * priority levels (High / Low).
 * When disabled, all interrupts operate at the same level.
 */
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE                 INTERRUPT_FEATURE_ENABLE


/* ----------------------------------------------------
 * External Interrupt Configuration
 * ----------------------------------------------------
 */

/**
 * @brief Enable/Disable INT0, INT1, INT2 external interrupts
 */
#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable PORTB change interrupts (RB4?RB7)
 */
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE

/* ----------------------------------------------------
 * ADC Interrupt Configuration
 * ----------------------------------------------------
 */

/**
 * @brief Enable/Disable ADC interrupt
 */
#define ADC_INTERRUPT_FEATURE_ENABLE                     INTERRUPT_FEATURE_ENABLE


/* ----------------------------------------------------
 * Timer Interrupt Configuration
 * ----------------------------------------------------
 */

/**
 * @brief Enable/Disable Timer0 interrupt
 */
#define TIMER0_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable Timer1 interrupt
 */
#define TIMER1_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable Timer2 interrupt
 */
#define TIMER2_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable Timer3 interrupt
 */
#define TIMER3_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE

/* ----------------------------------------------------
 * CCP Interrupt Configuration
 * ----------------------------------------------------
 */

/**
 * @brief Enable/Disable CCP1 interrupt
 */
#define CCP1_INTERRUPT_FEATURE_ENABLE                    INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable CCP2 interrupt
 */
#define CCP2_INTERRUPT_FEATURE_ENABLE                    INTERRUPT_FEATURE_ENABLE

/* ----------------------------------------------------
 * EUSART Interrupt Configuration
 * ----------------------------------------------------
 */

/**
 * @brief Enable/Disable EUSART transmit interrupt
 */
#define EUSART_TX_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable EUSART receive interrupt
 */
#define EUSART_RX_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE

/* ----------------------------------------------------
 * MSSP (SPI / I2C) Interrupt Configuration
 * ----------------------------------------------------
 */

/**
 * @brief Enable/Disable MSSP SPI interrupt
 */
#define MSSP_SPI_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable MSSP I2C interrupt
 */
#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE

/**
 * @brief Enable/Disable MSSP I2C Bus Collision interrupt
 */
#define MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE        INTERRUPT_FEATURE_ENABLE


#endif	/* MCAL_INTERRUPT_GEN_CFG_H */ 


