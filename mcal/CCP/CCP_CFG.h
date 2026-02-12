/**
 * @file    CCP_CFG.h
 * @brief   CCP Driver Configuration File
 * @author  Abdelmoniem Ahmed
 *
 * @details
 * This file contains compile-time configuration options
 * for CCP1 and CCP2 peripherals.
 *
 * Users can select:
 *  - Capture Mode
 *  - Compare Mode
 *  - PWM Mode
 *
 * Configuration is performed using preprocessor macros.
 *
 * Target MCU: PIC18F4620
 */

#ifndef CCP_CFG_H
#define	CCP_CFG_H

/* Section : Includes */


/* Section : Macro Declaration */

/* CCP Mode Options */
#define CCP_CFG_CAPTURE_MODE_SELECTED  0X00
#define CCP_CFG_COMPARE_MODE_SELECTED  0X01
#define CCP_CFG_PWM_MODE_SELECTED      0X02

/**
 * @brief Select operating mode for CCP1
 * Available Options:
 *  - CCP_CFG_CAPTURE_MODE_SELECTED
 *  - CCP_CFG_COMPARE_MODE_SELECTED
 *  - CCP_CFG_PWM_MODE_SELECTED
 */
#define CCP1_CFG_SELECTED_MODE           (CCP_CFG_PWM_MODE_SELECTED)

/**
 * @brief Select operating mode for CCP2
 * Available Options:
 *  - CCP_CFG_CAPTURE_MODE_SELECTED
 *  - CCP_CFG_COMPARE_MODE_SELECTED
 *  - CCP_CFG_PWM_MODE_SELECTED
 */
#define CCP2_CFG_SELECTED_MODE           (CCP_CFG_CAPTURE_MODE_SELECTED)


/* Section : Macro Functions Declarations */


/* Section : Data Types Declarations */


/* Section : Function Declarations */


#endif	/* CCP_CFG_H */

