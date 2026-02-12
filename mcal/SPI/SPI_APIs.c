/**
 * @file SPI_APIs.c
 * @brief MSSP SPI Driver Implementation for PIC18F4620
 *
 * @details
 * This file contains the implementation of the MSSP peripheral
 * configured in SPI mode (Master/Slave).
 *
 * The driver supports:
 *  - Master and Slave modes
 *  - Configurable clock polarity and edge
 *  - Optional interrupt-driven operation
 *  - GPIO abstraction for SPI pins
 *
 * This implementation follows:
 *  - Bare-metal embedded architecture
 *  - MCAL layering principle
 *  - Configurable interrupt support
 *
 * Layer  : MCAL (Microcontroller Abstraction Layer)
 * Target : PIC18F4620
 *
 * @author Abdelmoniem Ahmed
 * LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * 
 */

#include "SPI_APIs.h"

/* ============================= */
/* Section : Static Declarations */
/* ============================= */


#if         INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
    /**
    * @brief Pointer to user-defined SPI interrupt handler.
    */
    static void (* MSSP_SPI_InterruptHandler) (void) = NULL ;
#endif

/**
 * @brief SPI pin configurations (PIC18F4620 hardware mapping).
 *
 * SPI Pins:
 *  - SDO  -> RC5
 *  - SDI  -> RC4
 *  - SCK  -> RC3
 *  - SS   -> RA5
 */
    
static pin_config_t MSSP_SPI_SDO  = { .port = PORTC_INDEX , .pin = PIN5 } ;
static pin_config_t MSSP_SPI_SDI  = { .port = PORTC_INDEX , .pin = PIN4 } ;
static pin_config_t MSSP_SPI_SCLK = { .port = PORTC_INDEX , .pin = PIN3 } ;
static pin_config_t MSSP_SPI_SS   = { .port = PORTA_INDEX , .pin = PIN5 } ; 


/* ============================= */
/* Section : Static Prototypes   */
/* ============================= */


static void MSSP_SPI_Select_Mode_Set(const mssp_spi_t *spi_obj);
static void MSSP_SPI_CLOCK_Init(const mssp_spi_t *spi_obj);
static void MSSP_SPI_Sample_At(const mssp_spi_t *spi_obj);
static void MSSP_SPI_Slave_Init_Pins(const mssp_spi_t *spi_obj);
static void MSSP_SPI_Master_Init_Pins(const mssp_spi_t *spi_obj);

/* ============================= */
/* Section : API Implementations */
/* ============================= */


Std_ReturnType MSSP_SPI_Init(mssp_spi_t *spi_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == spi_obj){
        ret = E_NOT_OK;
    }
    else{
     
        uint8 dummy_data = ZERO_INIT;
        
        MSSP_SPI_DISABLE();
        
        MSSP_SPI_WRITE_COLLISION_CLEAR();
        MSSP_SPI_OVERFLOW_CLEAR();
        
        dummy_data = SSPBUF ;
        
        MSSP_SPI_Select_Mode_Set(spi_obj);
        MSSP_SPI_CLOCK_Init(spi_obj);
        MSSP_SPI_Sample_At(spi_obj);
        if( (SPI_Slave_Slave_Select_Disable == spi_obj->spi_master_slave_select) ||
            (SPI_Slave_Slave_Select_Enable  == spi_obj->spi_master_slave_select) ){
                
                MSSP_SPI_Slave_Init_Pins(spi_obj);
        }
        else if((SPI_Master_CLK_FOSC_DIV4   == spi_obj->spi_master_slave_select) ||
                (SPI_Master_CLK_FOSC_DIV16  == spi_obj->spi_master_slave_select) ||
                (SPI_Master_CLK_FOSC_DIV64  == spi_obj->spi_master_slave_select) || 
                (SPI_Master_CLK_FTMR2_DIV2  == spi_obj->spi_master_slave_select) ){
                
                    MSSP_SPI_Master_Init_Pins(spi_obj);
        }
        
        /* Interrupt Configurations part */
        
#if         INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
     
        MSSP_SPI_INTERRUPT_DISABLE();
        MSSP_SPI_INTERRUPT_CLEAR_FLAG();
        MSSP_SPI_InterruptHandler = spi_obj->MSSP_SPI_DefaultInterruptHandler ;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_DISABLE
        
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        
        INTERRUPT_PriorityFeatureEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        
        if(Interrupt_High_Priority == spi_obj->mssp_spi_int_priority_level){
            MSSP_SPI_INTERRUPT_HIGH_PRIORITY();
        }
        else if(Interrupt_Low_Priority == spi_obj->mssp_spi_int_priority_level){
            MSSP_SPI_INTERRUPT_LOW_PRIORITY();
        }
        else{
            /* Nothing */
        }
        
#endif        
      
        MSSP_SPI_INTERRUPT_ENABLE();
        
#endif        
        
        /* End of Interrupt Configurations Setting */
        
        MSSP_SPI_ENABLE();
    }
    return ret ;
}

Std_ReturnType MSSP_SPI_DeInit(mssp_spi_t *spi_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == spi_obj){
        ret = E_NOT_OK;
    }
    else{
        
        uint8 dummy_data = ZERO_INIT;
        
        MSSP_SPI_WRITE_COLLISION_CLEAR();
        MSSP_SPI_OVERFLOW_CLEAR();
        
        dummy_data = SSPBUF ;

#if         INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
        
        MSSP_SPI_INTERRUPT_DISABLE();
        MSSP_SPI_INTERRUPT_CLEAR_FLAG();
        
#endif         
        MSSP_SPI_DISABLE();
                
    }
    return ret ;
}



Std_ReturnType MSSP_SPI_Transmit_Receive_Byte(uint8 data_transmit , uint8 * data_received){
    Std_ReturnType ret = E_OK;
    if(NULL == data_received){
        ret = E_NOT_OK;
    }
    else{
        MSSP_SPI_WRITE_COLLISION_CLEAR();
        MSSP_SPI_OVERFLOW_CLEAR();
#if  INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_INTERRUPT_CLEAR_FLAG();
#endif        
        *data_received = SSPBUF ;
        SSPBUF = data_transmit;
    }
    return ret ;
}


static void MSSP_SPI_Select_Mode_Set(const mssp_spi_t *spi_obj){
    MSSP_SPI_MODE_SELECT(spi_obj->spi_master_slave_select);
}


static void MSSP_SPI_CLOCK_Init(const mssp_spi_t *spi_obj){
    if( SPI_CLK_POL_IDLE_HIGH_CFG == spi_obj->spi_clock_polarity_select ){
        MSSP_SPI_CLK_POL_HIGH();
    }
    else {
        MSSP_SPI_CLK_POL_LOW();
    }
    if(SPI_CLKE_TRANSMISSION_ACTIVE_TO_IDLE_CFG == spi_obj->spi_clock_transmit_edge_select){
        MSSP_SPI_EDGE_FROM_ACTIVE_TO_IDLE_SELECT();
    }
    else{
        MSSP_SPI_EDGE_FROM_IDEL_TO_ACTIVE_SELECT();
    }
}


static void MSSP_SPI_Sample_At(const mssp_spi_t *spi_obj){
    if( (SPI_Slave_Slave_Select_Enable  == spi_obj->spi_master_slave_select) ||
        (SPI_Slave_Slave_Select_Disable == spi_obj->spi_master_slave_select)){
            MSSP_SPI_SLAVE_SAMPLE_TIME_MUST_CLEAR();
    }
    else{
        if(SPI_MASTER_SAMPLE_AT_END_CFG == spi_obj->spi_master_sample_at_select){
            MSSP_SPI_MASTER_SAMPLE_TIME_AT_END_SELECT();
        }
        else if (SPI_MASTER_SAMPLE_AT_MIDDLE_CFG == spi_obj->spi_master_sample_at_select){
            MSSP_SPI_MASTER_SAMPLE_TIME_AT_MIDDLE_SELECT();
        }
    }
}


static void MSSP_SPI_Slave_Init_Pins( const mssp_spi_t * spi_obj ){
    if(     ( SPI_TRANSMIT_ENABLE_CFG == spi_obj->spi_transmit_enable) 
        ||  ( SPI_RECEIVE_ENABLE_CFG  == spi_obj->spi_receive_enable) ){
        
        /* SDO , SDI , SCLK , SS Direction Select  */        
        
        MSSP_SPI_SCLK.direction = GPIO_DIRECTION_INPUT ;
        
        if(SPI_TRANSMIT_ENABLE_CFG == spi_obj->spi_transmit_enable){
            MSSP_SPI_SDO.direction = GPIO_DIRECTION_OUTPUT ;
        }
        else{ /* Nothing */ }
        if(SPI_RECEIVE_ENABLE_CFG == spi_obj->spi_receive_enable){
            MSSP_SPI_SDI.direction = GPIO_DIRECTION_INPUT ;
        }
        else{ /* Nothing */ }
        if( SPI_Slave_Slave_Select_Disable == spi_obj->spi_master_slave_select ){
            MSSP_SPI_SS.direction = GPIO_DIRECTION_OUTPUT;
        }
        else{
            MSSP_SPI_SS.direction = GPIO_DIRECTION_INPUT;
        }

       /* 
        * 
        * After select the direction according to the configurations now we will initialize these pins 
        * SDI , SDO , SCLK , SS
        *
        */
        gpio_pin_initialize(&MSSP_SPI_SCLK);
        gpio_pin_initialize(&MSSP_SPI_SDO);
        gpio_pin_initialize(&MSSP_SPI_SDI);
        gpio_pin_initialize(&MSSP_SPI_SS);
        
    }
    else{
        /* Slave Is not configured at all */
    }
}


static void MSSP_SPI_Master_Init_Pins(const mssp_spi_t *spi_obj){
    if(     ( SPI_TRANSMIT_ENABLE_CFG == spi_obj->spi_transmit_enable) 
        ||  ( SPI_RECEIVE_ENABLE_CFG  == spi_obj->spi_receive_enable) ){
        
        /* SDO , SDI , SCLK Direction Select  */        
        
        MSSP_SPI_SCLK.direction = GPIO_DIRECTION_OUTPUT ;
        
        if(SPI_TRANSMIT_ENABLE_CFG == spi_obj->spi_transmit_enable){
            MSSP_SPI_SDO.direction = GPIO_DIRECTION_OUTPUT ;
        }
        else{ /* Nothing */ }
        if(SPI_RECEIVE_ENABLE_CFG == spi_obj->spi_receive_enable){
            MSSP_SPI_SDI.direction = GPIO_DIRECTION_INPUT ;
        }
        else{ /* Nothing */ }

       /* 
        * 
        * After select the direction according to the configurations now we will initialize these pins 
        * SDI , SDO , SCLK , SS
        *
        */
        gpio_pin_initialize(&MSSP_SPI_SCLK);
        gpio_pin_initialize(&MSSP_SPI_SDO);
        gpio_pin_initialize(&MSSP_SPI_SDI);
        
    }
    else{
        /* Master Is not configured at all */
    }
}

/* ============================= */
/* Section : ISR                 */
/* ============================= */


/**
 * @brief MSSP SPI Interrupt Service Routine.
 *
 * Must be called inside global interrupt handler.
 */

void MSSP_SPI_ISR(void){
    
    MSSP_SPI_INTERRUPT_CLEAR_FLAG();
    MSSP_SPI_WRITE_COLLISION_CLEAR();
    MSSP_SPI_OVERFLOW_CLEAR();
    
    if(MSSP_SPI_InterruptHandler){
        MSSP_SPI_InterruptHandler();
    }
}

