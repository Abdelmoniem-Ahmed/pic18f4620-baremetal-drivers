/**
 * @file    I2C_APIs.c
 * @author  Abdelmoniem Ahmed
 * @LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/ 
 * @brief   MSSP I2C Driver Implementation for PIC18F4620
 *
 * @details
 * This file implements the MSSP peripheral in I2C mode.
 * All register-level operations follow the PIC18F4620
 * datasheet specifications.
 *
 * The driver supports both polling-based and interrupt-based
 * communication models.
 */

#include"I2C_APIs.h"

static pin_config_t MSSP_I2C_SDA  = { .port = PORTC_INDEX , .pin = PIN4 , .direction = GPIO_DIRECTION_INPUT} ;
static pin_config_t MSSP_I2C_CLK = { .port = PORTC_INDEX , .pin = PIN3 , .direction = GPIO_DIRECTION_INPUT} ;

#if         INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE
    static void (* MSSP_I2C_InterruptHandler) (void) = NULL ;
    static void (* MSSP_I2C_ReceiveOVERFLOW) (void) = NULL ;
#endif

#if         INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE    
    static void (* MSSP_I2C_Bus_Coll_InterruptHandler) (void) = NULL ;
#endif

/* Static Function Declaration */

static void MSSP_I2C_Slave_Mode_General_Call_Configuration(const mssp_i2c_t * i2c_obj);
static void MSSP_I2C_Slew_Rate_Configuration(const mssp_i2c_t * i2c_obj);
static void MSSP_I2C_SMBus_Configuration(const mssp_i2c_t * i2c_obj);
static inline void MSSP_I2C_PIN_CONFIG(void);
static inline void MSSP_I2C_Master_Mode_Clock_Configuration(const mssp_i2c_t * i2c_obj);

/* Global Function Definition */

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t * i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable MSSP I2C Module */
        MSSP_I2C_DISABLE_CFG();
        /* MSSP I2C Mode Select Configuration */
        MSSP_I2C_MODE_SELECT(i2c_obj->i2c_cfg.i2c_mode_cfg);
        /* MSSP I2C Select Mode */
        if(MSSP_I2C_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode){
            /* MSSP I2C Master Mode Configuration */
            
            /* MSSP I2C Master Mode Clock Configuration */
            MSSP_I2C_Master_Mode_Clock_Configuration(i2c_obj); 
        }
        else if(MSSP_I2C_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode){
            /* MSSP I2C Slave Mode Configuration */
            
            /* MSSP I2C Slave Mode General Call Configuration */
            MSSP_I2C_Slave_Mode_General_Call_Configuration(i2c_obj);
            /* Clear the Write Collision Detect */
            SSPCON1bits.WCOL = 0 ; /* No Collision */
            /* Clear the Receive Over Flow Indicator */
            SSPCON1bits.SSPOV = 0 ; /* No Overflow */
            /* Release the Clock */
            SSPCON1bits.CKP = 1 ; /* Release Clock */
            /* Assign the I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address ;
            /* I2C Slave Configuration */
            /* Function Like Macro Made It For Both Slave / Master */
            /* MSSP_I2C_MODE_SELECT(i2c_obj->i2c_cfg.i2c_mode_cfg); */
        }
        else{ /* Nothing */ }
        
        /* MSSP I2C Master / Slave Mode GPIO Pins Configuration */
        MSSP_I2C_PIN_CONFIG();
        /* MSSP I2C Slew Rate Configuration */
        MSSP_I2C_Slew_Rate_Configuration(i2c_obj);
        /* MSSP I2C SMBus Configuration */
        MSSP_I2C_SMBus_Configuration(i2c_obj);
        
        /* Default Interrupt Configurations */
#if                     INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE
        /* Disable the Interrupt */
        MSSP_I2C_INTERRUPT_DISABLE();
        /* Clear The Interrupt Flag */
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        /* Default Interrupt Priority COnfiguration */
#if                     INTERRUPT_FEATURE_DISABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE        
        /* If Priority Feature Disable */
        /* Global / Peripheral Interrupt Enable */
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#elif                   INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE 
        /* If Priority Feature Enable */
        INTERRUPT_PriorityFeatureEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        if(Interrupt_High_Priority == i2c_obj->mssp_i2c_int_priority_level){
            MSSP_I2C_INTERRUPT_HIGH_PRIORITY();
        }
        else{
            MSSP_I2C_INTERRUPT_LOW_PRIORITY();
        }
#endif  
        MSSP_I2C_InterruptHandler = i2c_obj->MSSP_I2C_DEFAULT_INTERRUPT_HANDLER ;
        MSSP_I2C_ReceiveOVERFLOW  = i2c_obj->MSSP_I2C_REPORT_RECEIVE_OVERFLOW ;
        MSSP_I2C_INTERRUPT_ENABLE();
#endif

        /* Bus Collision Interrupt Configurations */
#if                     INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE
        /* Disable the Interrupt */
        MSSP_I2C_BUS_COLL_INTERRUPT_DISABLE();
        /* Clear The Interrupt Flag */
        MSSP_I2C_BUS_COLL_INTERRUPT_CLEAR_FLAG();
        
        /* Bus Collision Interrupt Priority COnfiguration */
#if                     INTERRUPT_FEATURE_DISABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE        
        /* If Priority Feature Disable */
        /* Global / Peripheral Interrupt Enable */
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#elif                   INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE 
        /* If Priority Feature Enable */
        INTERRUPT_PriorityFeatureEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        if(Interrupt_High_Priority == i2c_obj->mssp_i2c_Bus_COL_int_priority_level){
            MSSP_I2C_BUS_COLL_INTERRUPT_HIGH_PRIORITY();
        }
        else{
            MSSP_I2C_BUS_COLL_INTERRUPT_LOW_PRIORITY();
        }
#endif  
        MSSP_I2C_Bus_Coll_InterruptHandler = i2c_obj->MSSP_I2C_REPORT_WRITE_COLLISION ;
        MSSP_I2C_BUS_COLL_INTERRUPT_ENABLE();
#endif        
        /* Enable MSSP I2C Module Enable */
        MSSP_I2C_ENABLE_CFG(); 
    }
    return ret ; 
    
}



Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t * i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable MSSP I2C Module */
        MSSP_I2C_DISABLE_CFG();
        
        /* Disable MSSP I2C Default Interrupt */
#if                     INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE
        /* Disable the Interrupt */
        MSSP_I2C_INTERRUPT_DISABLE();        
#endif
        
        /* Disable MSSP I2C Bus Collision Interrupt */
#if                     INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE
        /* Disable the Interrupt */
        MSSP_I2C_BUS_COLL_INTERRUPT_DISABLE();
#endif          
    }
    return ret ; 
    
}



Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t * i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initiates the start condition on SDA and CLK Pin*/
        SSPCON2bits.SEN = 1 ; /* Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware */ 
        /* wait for the completion of start condition */
        while(SSPCON2bits.SEN);
        /* Clear interrupt flag on start condition event */
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        /* Report the start condition Detection */
        if( START_CONDITION_DETECTED == SSPSTATbits.S){
            ret = E_OK ;
        }
        else if( START_CONDITION_NOT_DETECTED == SSPSTATbits.S ){
            ret = E_NOT_OK ;
        }
        else{ /* Nothing */ }
    }
    return ret ; 
    
}



Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t * i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initiates the repeated start condition on SDA and CLK Pin*/
        SSPCON2bits.RSEN = 1 ; /* Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
        /* wait for the completion of repeated start condition */
        while(SSPCON2bits.RSEN);
        /* Clear interrupt flag on repeated start condition event */
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();        
    }
    return ret ; 
}



Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t * i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initiates the Stop condition on SDA and CLK Pin*/
        SSPCON2bits.PEN = 1 ; /* Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware */
        /* wait for the completion of Stop condition */
        while(SSPCON2bits.PEN);
        /* Clear interrupt flag on Stop condition event */
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();        
        /* Report the Stop condition Detection */
        if( STOP_CONDITION_DETECTED == SSPSTATbits.P ){
            ret = E_OK ;
        }
        else if( STOP_CONDITION_NOT_DETECTED == SSPSTATbits.P ){
            ret = E_NOT_OK ;
        }
        else{ /* Nothing */ }
    }
    return ret ;
}



Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t * i2c_obj , uint8 i2c_data , uint8 *_ack){
    Std_ReturnType ret = E_OK;
    if((NULL == i2c_obj) || (NULL == _ack)){
        ret = E_NOT_OK;
    }
    else{
        /* Write data to the Data Register */
        SSPBUF = i2c_data ;
        /* Wait the Transmission to be Completed */
        while(!PIR1bits.SSPIF);
        /* TODO: Add timeout protection to avoid infinite blocking */
        /* Clear The MSSP Interrupt Flag -> SSPIF */
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        
        /* Report The acknowledge receive from the Slave */
        if(I2C_ACK_REC_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *_ack = I2C_ACK_REC_FROM_SLAVE ;
        }
        else{
            *_ack = I2C_ACK_NOT_REC_FROM_SLAVE ;
        }
        ret = E_OK ;
    }
    return ret ; 
    
}



Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t * i2c_obj , uint8 ack ,uint8 * i2c_data){
    Std_ReturnType ret = E_OK;
    if((NULL == i2c_obj) || (NULL == i2c_data)){
        ret = E_NOT_OK;
    }
    else{
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* Wait for Buffer Full Flag : A Complete Byte Received */
        while(!SSPSTATbits.BF);
        /* TODO: Add timeout protection to avoid infinite blocking */
        /* Copy The Data Register to buffer variable */
        *i2c_data = SSPBUF ;
        /* Send ACK or NACK after read */
        if(I2C_MASTER_SEND_ACK == ack)
        {
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK ;
            SSPCON2bits.ACKEN = I2C_MASTER_REC_ACK_START ; /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. Automatically */
        }   
        else if(I2C_MASTER_SEND_NOT_ACK == ack){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NOT_ACK ;
            SSPCON2bits.ACKEN = I2C_MASTER_REC_ACK_START ; /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. Automatically */
        }
        else { /* Nothing */ }
    }
    return ret ; 
    
}


/* Static Function Definition */


static inline void MSSP_I2C_PIN_CONFIG(void){
    gpio_pin_initialize(&MSSP_I2C_SDA) ; /* Serial Data (SDA) is Input */
    gpio_pin_initialize(&MSSP_I2C_CLK) ; /* Serial Clock (CLK) is Input */   
}

static void MSSP_I2C_Slave_Mode_General_Call_Configuration(const mssp_i2c_t * i2c_obj){
    if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call ){
        I2C_GENERAL_CALL_ENABLE_CFG();
    }
    else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call){
        I2C_GENERAL_CALL_DISABLE_CFG();
    }
    else{ /* Nothing */ }
}

static void MSSP_I2C_Slew_Rate_Configuration(const mssp_i2c_t * i2c_obj){
    if(I2C_SLEW_RATE_ENABLE_100kHZ == i2c_obj->i2c_cfg.i2c_slew_rate){
        I2C_SLEW_RATE_ENABLE_CFG();
    }
    else if (I2C_SLEW_RATE_DISABLE_400kHZ == i2c_obj->i2c_cfg.i2c_slew_rate){
        I2C_SLEW_RATE_DISABLE_CFG();
    }
    else { /* Nothing */ }
}

static void MSSP_I2C_SMBus_Configuration(const mssp_i2c_t * i2c_obj){
    if( I2C_SMBUS_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_Control){
        I2C_SMBUS_ENABLE_CFG();
    }
    else if ( I2C_SMBUS_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_Control){
        I2C_SMBUS_DISABLE_CFG();
    }
    else { /* Nothing */ }
}

static inline void MSSP_I2C_Master_Mode_Clock_Configuration(const mssp_i2c_t * i2c_obj){
    SSPADD = (uint8) (( _XTAL_FREQ / (4 * i2c_obj->i2c_clock) ) - 1) ;    
}

/* Interrupt Service Routines */

/**
 * @brief MSSP I2C Interrupt Service Routine
 *
 * Clears interrupt flag and calls user-defined
 * callback if registered.
 */
void MSSP_I2C_ISR(void){
#if                     INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE    
    MSSP_I2C_INTERRUPT_CLEAR_FLAG();
    if(MSSP_I2C_InterruptHandler){
        MSSP_I2C_InterruptHandler();
    }    
    else{ /* Nothing */ }
#endif    
    
}

/**
 * @brief MSSP I2C Bus Collision Interrupt Service Routine
 *
 * Clears collision flag and invokes collision callback.
 */
void MSSP_I2C_BC_ISR(void){
#if   INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE    
    MSSP_I2C_BUS_COLL_INTERRUPT_CLEAR_FLAG();
    if(MSSP_I2C_Bus_Coll_InterruptHandler){
        MSSP_I2C_Bus_Coll_InterruptHandler();
    }
    else{ /* Nothing */ }
#endif    
}

