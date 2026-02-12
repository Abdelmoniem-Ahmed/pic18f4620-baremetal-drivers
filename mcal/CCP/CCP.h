/**
 * @file    CCP.h
 * @brief   CCP (Capture/Compare/PWM) Driver Header File for PIC18F4620
 * @author  Abdelmoniem Ahmed
 *
 * @details
 * This file contains the public APIs, macros, data types, and configuration
 * structures for the CCP1/CCP2 peripheral driver.
 *
 * The CCP peripheral supports:
 *  - Capture Mode  (Timer value latching on input edge)
 *  - Compare Mode  (Output action on timer match)
 *  - PWM Mode      (Hardware Pulse Width Modulation)
 *
 * This driver follows:
 *  - MCAL Layered Architecture
 *  - Modular and Configurable Design
 *  - Interrupt Callback Mechanism
 *  - Bare-Metal Embedded Best Practices
 *
 * Target MCU: PIC18F4620
 *
 * GitHub Repository:
 * https://github.com/Abdelmoniem-Ahmed/pic18f4620-baremetal-drivers
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */


#ifndef CCP_H
#define	CCP_H


/* Section : Includes */

#include"std_types.h"
#include"hal_gpio.h"
#include"mcal_internal_interrupt.h"
#include"CCP_CFG.h"
#include"Timer2.h"
#include"timer1.h"
#include"Timer3.h"

/* Section : Macro Declaration */


#define CCP_MODULE_DISABLED                    ((uint8)0X00)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH       ((uint8)0X02)

/* CCP Operating Modes */
#define CCP_CAPTURE_MODE_EVERY_1_FALLING_EDGE  ((uint8)0X04)
#define CCP_CAPTURE_MODE_EVERY_1_RISING_EDGE   ((uint8)0X05)
#define CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE   ((uint8)0X06)
#define CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE  ((uint8)0X07)
#define CCP_COMPARE_MODE_SET_PIN_LOW           ((uint8)0X08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH          ((uint8)0X09)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT      ((uint8)0X0A)
#define CCP_COMPARE_MODE_GEN_EVENT             ((uint8)0X0B)
#define CCP_PWM_MODE                           ((uint8)0X0C)

/* Capture Status */
#define CCP_CAPTURE_NOT_READY  0X00
#define CCP_CAPTURE_READY      0X01

/* Compare Status */
#define CCP_COMPARE_NOT_READY  0X00
#define CCP_COMPARE_READY      0X01

/* Section : Macro Functions Declarations */

/**
 * @brief Sets CCP1 operating mode.
 */
#define CCP1_SET_MODE(__CONFIG)                 (CCP1CONbits.CCP1M = __CONFIG)

/**
 * @brief Sets CCP2 operating mode.
 */
#define CCP2_SET_MODE(__CONFIG)                 (CCP2CONbits.CCP2M = __CONFIG)

/* Section : Data Types Declarations */

/**
 * @brief CCP Register 16-bit Access Union
 *
 * Provides access to CCPRx register as:
 *  - Two 8-bit registers (Low & High)
 *  - Single 16-bit combined value
 */
typedef union{
    struct {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16Bit ;
    };
}CCP_REG_T ;

/**
 * @brief CCP module instance selection
 */
typedef enum{
    CCP1_INST,
    CCP2_INST        
}ccp_inst_t;

/**
 * @brief Timer selection for Capture/Compare modes
 */
typedef enum{
    CCP_CAPTURE_COMPARE_TMR1 = 0,
    CCP2_CAP_COM_TMR3_CCP1_CAP_COM_TMR1,
    CCP_CAPTURE_COMPARE_TMR3        
}ccp_timers_cfg_t;


/**
 * @brief CCP operating mode selection
 */
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED        
}ccp_mode_t;

/**
 * @brief CCP configuration structure
 *
 * This structure is used to configure:
 *  - CCP instance (CCP1 / CCP2)
 *  - Operating mode
 *  - Mode variant (edge type, compare action, etc.)
 *  - Associated GPIO pin
 *  - Timer selection (Timer1/Timer3)
 *  - PWM parameters (if PWM mode selected)
 *  - Interrupt configuration (if enabled)
 */
typedef struct{
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;
    pin_config_t pin;
#if (INTERRUPT_FEATURE_ENABLE == CCP1_INTERRUPT_FEATURE_ENABLE)
    void (* CCP_InterruptHandler)(void);
#if ( INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE)
    INTERRUPT_Priority_cfg priority;
#endif    
#endif
    
#if (CCP_CFG_PWM_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_PWM_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
    uint32 PWM_Frequency;
    uint8 timer2_prescaler_division : 2 ;
#endif    

#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
    ccp_timers_cfg_t tmr13_cfg;
#endif
    
}ccp_t;


/* Section : Function Declarations */

/**
 * @brief  Initializes the selected CCP peripheral.
 *
 * @details
 * This function configures the CCP module according to the
 * user-provided configuration structure.
 *
 * Depending on the selected operating mode, this function will:
 *  - Configure the CCP operating mode (Capture / Compare / PWM)
 *  - Configure the associated timer (Timer1 / Timer3 / Timer2)
 *  - Configure the CCP I/O pin direction
 *  - Configure interrupt settings (if enabled)
 *
 * @param[in] _ccp_obj  Pointer to a valid CCP configuration structure.
 *
 * @return
 *      E_OK     : Operation completed successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */
    Std_ReturnType CCP_Init(const ccp_t * _ccp_obj);
    
/**
 * @brief  De-initializes the selected CCP peripheral.
 *
 * @details
 * This function disables the CCP module and resets it to
 * its default reset state.
 *
 * The CCP output pin will be returned to its default state.
 *
 * @param[in] _ccp_obj  Pointer to a valid CCP configuration structure.
 *
 * @return
 *      E_OK     : Operation completed successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */    
    Std_ReturnType CCP_DeInit(const ccp_t * _ccp_obj);

#if (CCP_CFG_PWM_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_PWM_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)

/**
 * @brief  Updates the PWM duty cycle.
 *
 * @details
 * This function updates the PWM duty cycle value without
 * stopping the PWM signal generation.
 *
 * The duty cycle value is written to the CCP duty cycle registers
 * (CCPRxL and CCPxCON<5:4>) according to the PWM resolution.
 *
 * @param[in] _ccp_obj  Pointer to a valid CCP configuration structure.
 * @param[in] _duty     Duty cycle value (0?100 percentage).
 *
 * @return
 *      E_OK     : Duty cycle updated successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */    
    Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj , const uint8 _duty);
 
/**
 * @brief  Starts PWM signal generation.
 *
 * @details
 * This function enables the PWM mode and starts signal
 * generation on the configured CCP output pin.
 *
 * Timer2 must be properly configured before calling this function.
 *
 * @param[in] _ccp_obj  Pointer to a valid CCP configuration structure.
 *
 * @return
 *      E_OK     : PWM started successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */    
    Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj);
 
/**
 * @brief  Stops PWM signal generation.
 *
 * @details
 * This function disables PWM mode and forces the CCP output
 * to the idle state.
 *
 * @param[in] _ccp_obj  Pointer to a valid CCP configuration structure.
 *
 * @return
 *      E_OK     : PWM stopped successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */    
    Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj);
#endif    
    
#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || ((CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE))

/**
 * @brief  Checks whether new capture data is available.
 *
 * @details
 * This function checks the capture status flag to determine
 * whether a new timer value has been captured.
 *
 * @param[in]  _ccp_obj         Pointer to a valid CCP configuration structure.
 * @param[out] _capture_status  Pointer to variable that will contain:
 *                              - CCP_CAPTURE_READY
 *                              - CCP_CAPTURE_NOT_READY
 *
 * @return
 *      E_OK     : Status retrieved successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */
    Std_ReturnType CCP_IsCaptureDataReady(const ccp_t * _ccp_obj , uint8 * _capture_status);
    
/**
 * @brief  Reads the captured timer value.
 *
 * @details
 * This function reads the latched timer value stored in
 * the CCPRx registers after a capture event occurs.
 *
 * @param[in]  _ccp_obj        Pointer to a valid CCP configuration structure.
 * @param[out] capture_value   Pointer to variable that will store
 *                             the captured 16-bit timer value.
 *
 * @return
 *      E_OK     : Capture value read successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */    
    Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t * _ccp_obj , uint16 * capture_value);
#endif

#if (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
    
/**
 * @brief  Checks whether a compare match event occurred.
 *
 * @details
 * This function checks the compare status flag to determine
 * whether the timer value matched the programmed compare value.
 *
 * @param[in]  _ccp_obj         Pointer to a valid CCP configuration structure.
 * @param[out] _compare_status  Pointer to variable that will contain:
 *                              - CCP_COMPARE_READY
 *                              - CCP_COMPARE_NOT_READY
 *
 * @return
 *      E_OK     : Status retrieved successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */
    Std_ReturnType CCP_IsCompareComplete(const ccp_t * _ccp_obj , uint8 * _compare_status);
    
/**
 * @brief  Sets the compare match value.
 *
 * @details
 * This function writes a 16-bit compare value to the CCPRx registers.
 * When the selected timer matches this value, the configured compare
 * action will be executed.
 *
 * @param[in] _ccp_obj       Pointer to a valid CCP configuration structure.
 * @param[in] compare_value  16-bit timer match value.
 *
 * @return
 *      E_OK     : Compare value set successfully.
 *      E_NOT_OK : Operation failed due to invalid parameters.
 */
    Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t * _ccp_obj , uint16 compare_value);
#endif


#endif	/* CCP_H */

