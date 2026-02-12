/**
 * @file    CCP.c
 * @brief   CCP (Capture/Compare/PWM) Driver Source File
 * @author  Abdelmoniem Ahmed
 *
 * @details
 * This file contains the implementation of the CCP driver
 * for the PIC18F4620 microcontroller.
 *
 * Public APIs are documented in:
 *      CCP.h
 *
 * This source file contains:
 *  - Mode configuration logic
 *  - Timer selection handling
 *  - PWM duty cycle computation
 *  - Interrupt management
 *  - Internal helper functions
 *  - ISR implementations
 *
 * The implementation follows:
 *  - Register-level configuration
 *  - Modular MCAL design
 *  - Defensive parameter checking
 *  - Interrupt callback abstraction
 *
 * Target MCU: PIC18F4620
 *
 * GitHub Repository:
 * https://github.com/Abdelmoniem-Ahmed/pic18f4620-baremetal-drivers
 *
 * LinkedIn:
 * https://www.linkedin.com/in/abdelmoniem-ahmed/
 */


#include"CCP.h"

/**
 * @brief  Configures Timer1/Timer3 selection for Capture/Compare modes.
 *
 * @details
 * This internal helper function configures the T3CCP1 and T3CCP2
 * control bits to select which timer source is connected to
 * the CCP module in Capture or Compare modes.
 *
 * This function is used internally during CCP initialization.
 */
static void CCP_CAPTURE_COMPARE_TIMERS_CFG_SET(const ccp_t * _ccp_obj);


#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief  CCP1 interrupt callback function pointer.
 *
 * @details
 * Holds the user-defined interrupt handler registered
 * during CCP initialization.
 */
    static void (* CCP1_InterruptHandler)(void) = NULL; 
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief  CCP2 interrupt callback function pointer.
 *
 * @details
 * Holds the user-defined interrupt handler registered
 * during CCP initialization.
 */    
    static void (* CCP2_InterruptHandler)(void) = NULL; 
#endif    
    
/* Refer to CCP.h for function documentation */    
Std_ReturnType CCP_Init(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    uint32 l_PR2 = 0;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable ccp module */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLED);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLED);
        } 
        /* Pin Configuration */
        ret = gpio_pin_initialize(&(_ccp_obj->pin));
        /* CCP Initialize Capture Mode */
        if(CCP_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
            if(CCP1_INST == _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_mode_variant){
                    case CCP_CAPTURE_MODE_EVERY_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_EVERY_1_FALLING_EDGE); 
                        break;
                    case CCP_CAPTURE_MODE_EVERY_1_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_EVERY_1_RISING_EDGE); 
                        break;
                    case CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE) ; 
                        break;
                    case CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE) ; 
                        break;
                    default : ret = E_NOT_OK; 
                }
            }
            else{
                switch(_ccp_obj->ccp_mode_variant){
                    case CCP_CAPTURE_MODE_EVERY_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_EVERY_1_FALLING_EDGE); 
                        break;
                    case CCP_CAPTURE_MODE_EVERY_1_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_EVERY_1_RISING_EDGE); 
                        break;
                    case CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE) ; 
                        break;
                    case CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE) ; 
                        break;
                    default : ret = E_NOT_OK; 
                }
            }
#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)            
            CCP_CAPTURE_COMPARE_TIMERS_CFG_SET(_ccp_obj);
#endif
        }        
        /* CCP Initialize Compare Mode */
        else if(CCP_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            if(CCP1_INST == _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_mode_variant){
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); 
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_LOW : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW); 
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH) ; 
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT) ; 
                        break;
                    case CCP_COMPARE_MODE_GEN_EVENT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT) ; 
                        break;
                    default : ret = E_NOT_OK;     
                }
            }
            else{
                switch(_ccp_obj->ccp_mode_variant){
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); 
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_LOW : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW); 
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH) ; 
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT) ; 
                        break;
                    case CCP_COMPARE_MODE_GEN_EVENT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT) ; 
                        break;
                    default : ret = E_NOT_OK;     
                }
            }
#if (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)            
            CCP_CAPTURE_COMPARE_TIMERS_CFG_SET(_ccp_obj);
#endif            
        }
        /* CCP Initialize PWM Mode */
#if (CCP_CFG_PWM_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_PWM_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)                    
        else if(CCP_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
            if(CCP1_INST == _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_mode_variant){
                    case CCP_PWM_MODE : CCP1_SET_MODE(CCP_PWM_MODE);
                        break;
                    default : ret = E_NOT_OK;    
                }    
            }
            else{
                switch(_ccp_obj->ccp_mode_variant){
                    case CCP_PWM_MODE : CCP2_SET_MODE(CCP_PWM_MODE);
                        break;
                    default : ret = E_NOT_OK;    
                }
            }
        /* PWM Period Register (PR2) Calculation:
        * PR2 = (Fosc / (4 * PWM_Frequency * Prescaler)) - 1
        */            
            PR2 = (uint8)(_XTAL_FREQ /( (uint32)(_ccp_obj->PWM_Frequency) * (_ccp_obj->timer2_prescaler_division) * 4)) -1 ;
        } 
#endif
        else{
            ret = E_NOT_OK;
        }
        /* Interrupt Configuration */
#if (CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) || (CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_INTERRUPT_ENABLE();
            CCP1_INTERRUPT_CLEAR_FLAG();
            CCP1_InterruptHandler = _ccp_obj->CCP_InterruptHandler;
        }
        else{
            CCP2_INTERRUPT_ENABLE();
            CCP2_INTERRUPT_CLEAR_FLAG();
            CCP2_InterruptHandler = _ccp_obj->CCP_InterruptHandler;
        }
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityFeatureEnable();
        if( Interrupt_High_Priority == _ccp_obj->priority ){
            if(CCP1_INST == _ccp_obj->ccp_inst){
                CCP1_INTERRUPT_HIGH_PRIORITY();
            }
            else{
                CCP2_INTERRUPT_HIGH_PRIORITY();
            }
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{
            if(CCP1_INST == _ccp_obj->ccp_inst){
                CCP1_INTERRUPT_LOW_PRIORITY();
            }
            else{
                CCP2_INTERRUPT_LOW_PRIORITY();
            }
            INTERRUPT_GlobalInterruptLowEnable();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif    
        
    }
    return ret;
}
    
/* Refer to CCP.h for function documentation */ 
    Std_ReturnType CCP_DeInit(const ccp_t * _ccp_obj){
        Std_ReturnType ret = E_OK;
        if(NULL == _ccp_obj){
            ret = E_NOT_OK;
        }
        else{
            if(CCP1_INST == _ccp_obj->ccp_inst){
                CCP1_SET_MODE(CCP_MODULE_DISABLED);
#if  CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif                      
            }
            else{
                CCP2_SET_MODE(CCP_MODULE_DISABLED);
#if  CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE();
#endif                 
            }
        }
        return ret;
    }

#if (CCP_CFG_PWM_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_PWM_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
/* Refer to CCP.h for function documentation */ 
    Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj , const uint8 _duty){
        Std_ReturnType ret = E_OK;
        uint16 l_duty_temp = PR2;

        l_duty_temp = (uint16)(4 * (_duty/100.0)*(PR2+1));
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (l_duty_temp & 0x003);
            CCPR1L = (uint8)(l_duty_temp >> 2);            
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (l_duty_temp & 0x003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
        else{
            ret = E_NOT_OK;
        }
        return ret;
    }
/* Refer to CCP.h for function documentation */ 
    Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj){
        Std_ReturnType ret = E_OK;
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_PWM_MODE);            
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
        else{
            ret = E_NOT_OK;
        }
        return ret;
    }
/* Refer to CCP.h for function documentation */     
    Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj){
        Std_ReturnType ret = E_OK;
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLED);            
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLED);
        }
        else{
            ret = E_NOT_OK;
        }        
        return ret;
    }
    
#endif    
    
#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
/* Refer to CCP.h for function documentation */     
    Std_ReturnType CCP_IsCaptureDataReady(const ccp_t * _ccp_obj , uint8 * _capture_status){
        Std_ReturnType ret = E_OK;
        if((NULL == _capture_status) || (NULL == _ccp_obj)){
            ret = E_NOT_OK;
        }
        else{
            if(CCP1_INST == _ccp_obj->ccp_inst){
                if(CCP_CAPTURE_READY == PIR1bits.CCP1IF ){
                    *_capture_status = CCP_CAPTURE_READY;
                    CCP1_INTERRUPT_CLEAR_FLAG();
                }
                else{
                    *_capture_status = CCP_CAPTURE_NOT_READY;
                }
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst){
                if(CCP_CAPTURE_READY == PIR2bits.CCP2IF ){
                    *_capture_status = CCP_CAPTURE_READY;
                    CCP2_INTERRUPT_CLEAR_FLAG();
                }
                else{
                    *_capture_status = CCP_CAPTURE_NOT_READY;
                }
            }
        }
        return ret;
    }
/* Refer to CCP.h for function documentation */     
    Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t * _ccp_obj , uint16 * capture_value){
        Std_ReturnType ret = E_OK;
        CCP_REG_T capture_temp_val;
        capture_temp_val.ccpr_16Bit = 0;
        if((NULL == capture_value) || (NULL == _ccp_obj)){
            ret = E_NOT_OK;
        }
        else{
            if(CCP1_INST == _ccp_obj->ccp_inst){
                capture_temp_val.ccpr_low = CCPR1L;
                capture_temp_val.ccpr_high = CCPR1H;
                *capture_value = capture_temp_val.ccpr_16Bit ;
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst){
                capture_temp_val.ccpr_low = CCPR2L;
                capture_temp_val.ccpr_high = CCPR2H;
                *capture_value = capture_temp_val.ccpr_16Bit ;
            }
            else{  ret = E_NOT_OK ;  }
        }
        return ret;
    }
    
#endif

#if (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
/* Refer to CCP.h for function documentation */     
    Std_ReturnType CCP_IsCompareComplete(const ccp_t * _ccp_obj , uint8 * _compare_status){
        Std_ReturnType ret = E_OK;
        if((NULL == _compare_status) || (NULL == _ccp_obj)){
            ret = E_NOT_OK;
        }
        else{
            if(CCP1_INST == _ccp_obj->ccp_inst){
                if(CCP_COMPARE_READY == PIR1bits.CCP1IF ){
                    *_compare_status = CCP_COMPARE_READY;
                    CCP1_INTERRUPT_CLEAR_FLAG();
                }
                else{
                    *_compare_status = CCP_COMPARE_NOT_READY;
                }
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst){
                if(CCP_COMPARE_READY == PIR2bits.CCP2IF ){
                    *_compare_status = CCP_COMPARE_READY;
                    CCP2_INTERRUPT_CLEAR_FLAG();
                }
                else{
                    *_compare_status = CCP_COMPARE_NOT_READY;
                }
            }
            else{  ret = E_NOT_OK ;  }
        }
        return ret;
    }
/* Refer to CCP.h for function documentation */     
    Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t * _ccp_obj , uint16 compare_value){
        Std_ReturnType ret = E_OK;
        CCP_REG_T compare_temp_val;
        compare_temp_val.ccpr_16Bit = compare_value;
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCPR1L = compare_temp_val.ccpr_low;
            CCPR1H = compare_temp_val.ccpr_high;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCPR2L = compare_temp_val.ccpr_low;
            CCPR2H = compare_temp_val.ccpr_high;
        }
        else{ ret = E_NOT_OK ; }
        return ret;
    }
    
#endif

    
#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
/**
 * @brief  Internal timer routing configuration.
 *
 * @details
 * This function configures the Timer1/Timer3 routing to the
 * CCP modules by setting the T3CON control bits:
 *
 *  - T3CCP1
 *  - T3CCP2
 *
 * The selection depends on the user configuration stored
 * in the CCP configuration structure.
 *
 * This function is private to this source file.
 */    
static void CCP_CAPTURE_COMPARE_TIMERS_CFG_SET(const ccp_t * _ccp_obj){ 
    switch(_ccp_obj->tmr13_cfg){
        case CCP_CAPTURE_COMPARE_TMR1 : T3CONbits.T3CCP1 = 0 ; T3CONbits.T3CCP2 = 0 ;
            break;
        case CCP2_CAP_COM_TMR3_CCP1_CAP_COM_TMR1 : T3CONbits.T3CCP1 = 1 ; T3CONbits.T3CCP2 = 0 ;
            break;
        case CCP_CAPTURE_COMPARE_TMR3 : T3CONbits.T3CCP1 = 0 ; T3CONbits.T3CCP2 = 1 ;
            break;
        default : /* Nothing */   break; 
    }
}    
    
#endif    
    
    
    
    
    
    
#if (CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)   
/**
 * @brief  CCP1 Interrupt Service Routine.
 *
 * @details
 * This ISR clears the interrupt flag and executes the
 * registered user callback function if available.
 *
 * The callback function is assigned during CCP initialization.
 */
void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}   
#endif

#if  (CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
/**
 * @brief  CCP2 Interrupt Service Routine.
 *
 * @details
 * This ISR clears the interrupt flag and executes the
 * registered user callback function if available.
 *
 * The callback function is assigned during CCP initialization.
 */
void CCP2_ISR(void){
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}   
#endif