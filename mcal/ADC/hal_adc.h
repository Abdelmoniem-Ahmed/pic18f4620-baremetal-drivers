/**
 * @file    hal_adc.h
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   ADC Driver for PIC18F4620 (MCAL)
 * @details This header file provides macros, data types, and function 
 *          prototypes to configure and manage the internal ADC module
 *          of the PIC18F4620 microcontroller. It supports all ADC channels
 *          (AN0?AN12) with configurable acquisition time, conversion clock,
 *          result justification, voltage reference, and both polling and
 *          interrupt-driven conversion modes. Designed as an MCAL layer
 *          driver following a modular, portable, and reusable architecture.
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H



/* Section : Includes */

#include "xc.h"
#include"std_types.h"
#include"hal_gpio.h"
#include"mcal_internal_interrupt.h"

/* Section : Macro Declaration */

/**
 * @brief Analog/Digital pin configuration macros
 */
#define ADC_ALL_DIGITAL_FUNCTIONALITY    0x0F
#define ADC_AN0_ANALOG_FUNCTIONALITY     0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY     0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY     0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY     0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY     0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY     0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY     0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY     0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY     0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY     0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY    0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY    0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY    0x02

/**
 * @brief ADC result format
 */
#define ADC_RESULT_RIGHT                 0x01
#define ADC_RESULT_LEFT                  0x00
   
/**
 * @brief Voltage reference enable/disable
 */
#define ADC_VOLTAGE_REFERENCE_ENABLE     0x01
#define ADC_VOLTAGE_REFERENCE_DISABLE    0x00

/* Section : Macro Functions Declarations */

/**
 * @brief Check if ADC conversion is in progress
 */
#define ADC_CONVERSION_STATUS()          (ADCON0bits.GODONE)
#define ADC_CONVERSION_STARTS()          (ADCON0bits.GODONE = 1)


/** 
 *  @brief Analog to Digital Control
 *  @note    ADC_CONVERTER_ENABLE()    enable adc module
 *           ADC_CONVERTER_DISABLE()   disable adc module
 */
#define ADC_CONVERTER_ENABLE()           (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()          (ADCON0bits.ADON = 0)

/**
 * @brief Enable/disable external voltage reference
 */
#define ADC_DISABLE_VOLTAGE_REFRENCE()   do{ADCON1bits.VCFG1 = 0;\
                                            ADCON1bits.VCFG0 = 0;\
                                            }while(0)
                   

#define ADC_ENABLE_VOLTAGE_REFRENCE()   do{ADCON1bits.VCFG1 = 1 ;\
                                            ADCON1bits.VCFG0 = 1 ;\
                                            }while(0)

/**   @example if i use ADC_AN4_ANALOG_FUNCTIONALITY
 *             then each AN4,AN3,AN2,AN1,AN0 will be analog 
 */

/**
 * @brief Configure analog/digital port
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(__CONFIG)       (ADCON1bits.PCFG = __CONFIG)

/**
 * @brief Set result justification
 */
#define ADC_RESULT_RIGHT_FORMAT()                      (ADCON2bits.ADFM = 1)      
#define ADC_RESULT_LEFT_FORMAT()                       (ADCON2bits.ADFM = 0) 


/* Section : Data Types Declarations */

/**
 * @brief ADC channel selection
 */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1 ,
    ADC_CHANNEL_AN2 ,
    ADC_CHANNEL_AN3 ,
    ADC_CHANNEL_AN4 ,
    ADC_CHANNEL_AN5 ,
    ADC_CHANNEL_AN6 ,
    ADC_CHANNEL_AN7 ,
    ADC_CHANNEL_AN8 ,
    ADC_CHANNEL_AN9 ,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12         
}adc_channel_select_t;

/**
 * @brief ADC acquisition time selection
 */
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD        
}adc_acquisition_time_t;

/**
 * @brief ADC conversion clock selection
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8   ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32  ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4   ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16  ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64          
}adc_conversion_clock_t; 

/**
 * @brief ADC configuration structure
 */
typedef struct{
#if    INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler) (void);       /**< User callback for ADC interrupt */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;             /**< High/Low priority */
#endif
#endif    
    adc_acquisition_time_t  acquisition_time;   /**< ADC acquisition time */
    adc_conversion_clock_t  conversion_clock;   /**< ADC conversion clock */
    adc_channel_select_t    adc_channel     ;   /**< Selected channel */
    uint8 result_format          : 1;           /**< 1 = Right, 0 = Left */
    uint8 voltage_reference      : 1;           /**< 1 = Enable, 0 = Disable */
    uint8 adc_reserved           : 6;           /**< Reserved */
}adc_conf_t;

/**
 * @brief ADC conversion result type
 */
typedef uint16 adc_result_t;

/* Section : Function Declarations */

/**
 * @brief Initialize ADC with specified configuration
 * @param[in] _adc Pointer to ADC configuration structure
 * @return E_OK if successful, E_NOT_OK if invalid pointer
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc );

/**
 * @brief De-initialize ADC module
 * @param[in] _adc Pointer to ADC configuration structure
 * @return E_OK if successful, E_NOT_OK if invalid pointer
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc );

/**
 * @brief Select ADC channel
 * @param[in] channel ADC channel to select
 * @return E_OK if successful, E_NOT_OK if invalid channel
 */
Std_ReturnType ADC_Select_Channel( adc_channel_select_t channel);

/**
 * @brief Start ADC conversion
 * @param[in] _adc Pointer to ADC configuration
 * @return E_OK if successful, E_NOT_OK if invalid pointer
 */
Std_ReturnType ADC_Start_Conversion(const adc_conf_t *_adc );

/**
 * @brief Check if ADC conversion is complete
 * @param[in] _adc Pointer to ADC configuration
 * @param[out] Conversion_Status 0 = busy, 1 = done
 * @return E_OK if successful, E_NOT_OK if invalid pointer
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc , uint8 * Conversion_Status);

/**
 * @brief Get ADC conversion result
 * @param[in] _adc Pointer to ADC configuration
 * @param[out] Result Pointer to store ADC result
 * @return E_OK if successful, E_NOT_OK if invalid pointer or configuration
 */
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc , adc_result_t *Result);

/**
 * @brief Blocking call: select channel, start conversion, wait, and return result
 * @param[in] _adc Pointer to ADC configuration
 * @param[in] channel ADC channel to convert
 * @param[out] Result Pointer to store ADC result
 * @return E_OK if successful, E_NOT_OK if invalid parameters
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc , adc_channel_select_t channel 
                                          , adc_result_t *Result );


/**
 * @brief Start ADC conversion using interrupt
 * @param[in] _adc Pointer to ADC configuration
 * @param[in] channel ADC channel to convert
 * @return E_OK if successful, E_NOT_OK if invalid parameters
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc , adc_channel_select_t channel);

#endif	/* HAL_ADC_H */








