/**
 * @file    hal_adc.c
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   ADC Driver Implementation for PIC18F4620 (MCAL)
 * @details This source file implements functions for configuring and using
 *          the internal ADC module of the PIC18F4620. It provides both
 *          polling (blocking) and interrupt-driven conversion modes, with
 *          configurable acquisition time, conversion clock, result format,
 *          and voltage reference. The driver is designed following the MCAL
 *          layered architecture for portability and maintainability.
 */

#include"hal_adc.h"

#if    INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE
    static void (* ADC_InterruptHandler ) (void) = NULL;
#endif

static Std_ReturnType Set_result_format(const adc_conf_t *_adc );
static Std_ReturnType Set_voltage_reference(const adc_conf_t *_adc );
static Std_ReturnType set_channel_input(const adc_channel_select_t channel );

Std_ReturnType ADC_Init(const adc_conf_t *_adc ){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Config Acquisition time */
        ADCON2bits.ACQT = _adc->acquisition_time;
        /* Config Conversion time */
        ADCON2bits.ADCS = _adc->conversion_clock;
        /* Config The Result Format */
        ret = Set_result_format(_adc);
        /* Config The Default Channel */
        ADCON0bits.CHS = _adc->adc_channel;
        ret &= set_channel_input(_adc->adc_channel);
        /* Config The Voltage Reference */
        ret &= Set_voltage_reference(_adc);
        /* Config The Interrupt Handler */
#if    INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_CLEAR_FLAG();
        ADC_InterruptHandler = _adc->ADC_InterruptHandler; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        if(Interrupt_High_Priority == _adc->priority){
            ADC_INTERRUPT_HIGH_PRIORITY();
        }
        else if(Interrupt_Low_Priority == _adc->priority){
            ADC_INTERRUPT_LOW_PRIORITY();
        }
        INTERRUPT_PriorityFeatureEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
 
        ADC_INTERRUPT_ENABLE();
#endif  
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}

Std_ReturnType ADC_DeInit(const adc_conf_t *_adc ){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Disable interrupt feature */
#if    INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif    
    }
    return ret;
}

Std_ReturnType ADC_Select_Channel( adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    /* Config The Channel */
        ADCON0bits.CHS = channel;
        ret &= set_channel_input(channel);
    return ret;
}

Std_ReturnType ADC_Start_Conversion(const adc_conf_t *_adc ){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_CONVERSION_STARTS();
    }
    return ret;
}

Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc , uint8 * Conversion_Status){
    Std_ReturnType ret = E_OK;
    if((NULL == _adc) || (NULL == Conversion_Status)){
        ret = E_NOT_OK;
    }
    else{
        *Conversion_Status = (uint8)(!(ADCON0bits.GODONE)) ;
    }
    return ret;
}

Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc , adc_result_t *Result){
    Std_ReturnType ret = E_OK;
    if((NULL == _adc) || (NULL == Result)){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == _adc->result_format){
            *Result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format){
            *Result = (adc_result_t)((ADRESL >> 6) + (ADRESH*4));
        }
        else{
            ret = E_NOT_OK ;
        }
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc , adc_channel_select_t channel 
                                          , adc_result_t *Result ){
    Std_ReturnType ret = E_OK;
    if((NULL == _adc) || (NULL == Result)){
        ret = E_NOT_OK;
    }
    else{
        /* Select Channel */
        ret &= ADC_Select_Channel(channel);
        /* start ADC conversion */
        ret &= ADC_Start_Conversion(_adc);
        /* Wait for Covert The data */
        while(ADCON0bits.GO_DONE){ /* Blocking  */ }
        /* After The Conversion Done Get the Result */
        ret &=  ADC_GetConversionResult(_adc , Result);
    }
    return ret;
}


Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc , adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /* Select Channel */
        ret &= ADC_Select_Channel(channel);
        /* start ADC conversion */
        ret &= ADC_Start_Conversion(_adc);
    }
    return ret;
}



static Std_ReturnType Set_result_format(const adc_conf_t *_adc ){
    Std_ReturnType ret = E_OK;
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}


static Std_ReturnType set_channel_input(const adc_channel_select_t channel  ){
    Std_ReturnType ret = E_OK;
    switch(channel){
        case ADC_CHANNEL_AN0  : TRISAbits.RA0 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN1  : TRISAbits.RA1 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN2  : TRISAbits.RA2 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN3  : TRISAbits.RA3 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN4  : TRISAbits.RA5 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN5  : TRISEbits.RE0 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN6  : TRISEbits.RE1 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN7  : TRISEbits.RE2 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN8  : TRISBbits.RB2 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN9  : TRISBbits.RB3 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN10 : TRISBbits.RB1 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN11 : TRISBbits.RB4 = GPIO_DIRECTION_INPUT ;  break;
        case ADC_CHANNEL_AN12 : TRISBbits.RB0 = GPIO_DIRECTION_INPUT ;  break;
        default :   ret = E_NOT_OK ;                                break; 
    }
    return ret;
}


static Std_ReturnType Set_voltage_reference(const adc_conf_t *_adc ){
    Std_ReturnType ret = E_OK;
    if(ADC_VOLTAGE_REFERENCE_ENABLE == _adc->voltage_reference){
        ADC_ENABLE_VOLTAGE_REFRENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLE == _adc->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

#if    INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE

/**
 * @brief ADC Interrupt Service Routine
 * @details Clears ADC interrupt flag and calls user-defined callback if set.
 */
void ADC_ISR(void){
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}

#endif
