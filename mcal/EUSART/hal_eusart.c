/*
 * File:   hal_eusart.c
 * Author: Abdelmoniem Ahmed
 * LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
 *
 * Overview:
 * Implementation of the EUSART driver for PIC18F4620.
 * This file contains initialization, de-initialization, TX/RX configuration,
 * baud rate calculation, and interrupt service routines.
 *
 * Reference:
 * See hal_eusart.h for detailed function descriptions.
 */


#include"hal_eusart.h"


/* Section: Static Function Pointers for Interrupts */
#if   EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
   static void (* EUSART_TX_InterruptHandler)(void) = NULL ;
#endif
    
#if   EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (* EUSART_RX_InterruptHandler)(void) = NULL ;   
    static void (* EUSART_FERR_InterruptHandler)(void) = NULL ;
    static void (* EUSART_OERR_InterruptHandler)(void) = NULL ;
#endif


/* Section: Static Helper Functions */

/**
 * @brief Calculates and sets the EUSART baud rate registers.
 *
 * Configures SPBRG and SPBRGH according to the selected baud rate
 * and generator mode in the usart_t object.
 *
 * @param _usart_obj Pointer to the USART configuration object.
 */    
static void usart_baudrate_calculation(usart_t * _usart_obj );

/**
 * @brief Initializes the EUSART transmitter.
 *
 * Configures TX enable, 9-bit mode, and TX interrupt settings.
 *
 * @param _usart_obj Pointer to the USART configuration object.
 */
static void EUSART_ASYNC_TX_Init(usart_t * _usart_obj);

/**
 * @brief Initializes the EUSART receiver.
 *
 * Configures RX enable, 9-bit mode, and RX interrupts including error callbacks.
 *
 * @param _usart_obj Pointer to the USART configuration object.
 */
static void EUSART_ASYNC_RX_Init(usart_t * _usart_obj);


Std_ReturnType EUSART_ASYNC_Init(usart_t * _usart_obj){
    Std_ReturnType ret = E_OK ;
    
    if( NULL == _usart_obj ){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_DISABLE ;
        usart_baudrate_calculation(_usart_obj);
        EUSART_ASYNC_TX_Init(_usart_obj);
        EUSART_ASYNC_RX_Init(_usart_obj);
        
        
        TRISCbits.RC6 = GPIO_DIRECTION_INPUT ;
        TRISCbits.RC7 = GPIO_DIRECTION_INPUT ;
        RCSTAbits.SPEN = EUSART_ENABLE ;
        ret = E_OK ;
    }
    
    return ret ;
}

Std_ReturnType EUSART_ASYNC_DeInit(usart_t * _usart_obj){
    Std_ReturnType ret = E_OK ;
    
    if( NULL == _usart_obj ){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_DISABLE ;        
        ret = E_OK ;
    }
    
    return ret ;
}

Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(uint8 *_data){
    Std_ReturnType ret = E_OK ;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *_data = RCREG ;
        ret = E_OK ;
    }
    
    return ret ;
}

Std_ReturnType EUSART_ASYNC_Read_Byte_NonBlocking(uint8 *_data){
     Std_ReturnType ret = E_OK ;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
           *_data = RCREG ; 
        }
        else{ ret = E_NOT_OK ; }
    }
    return ret ;
}


Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking( uint8 _data){
    Std_ReturnType ret = E_OK ;
        while(!(TXSTAbits.TRMT));
#if   EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE         
        EUSART_TX_INTERRUPT_ENABLE();
#endif        
        TXREG = _data ;
        
    return ret ;
}

Std_ReturnType EUSART_ASYNC_Write_String_Blocking(uint8 *_data , uint16 str_length){
    Std_ReturnType ret = E_OK ;
    uint16 char_counter = ZERO_INIT;
    
    for(char_counter = ZERO_INIT ; char_counter < str_length ; char_counter++ ){
        ret = EUSART_ASYNC_Write_Byte_Blocking(_data[char_counter]);
    }
    
    return ret;
}

Std_ReturnType EUSART_ASYNC_Write_Byte_NonBlocking(uint8 _data){
        Std_ReturnType ret = E_OK ;
        if(TXSTAbits.TRMT){
#if   EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE         
            EUSART_TX_INTERRUPT_ENABLE();
#endif        
            TXREG = _data ;
        }
        
    return ret ;
}

Std_ReturnType EUSART_ASYNC_Write_String_NonBlocking(uint8 *_data , uint16 str_length){
    Std_ReturnType ret = E_OK ;
    uint16 char_counter = ZERO_INIT;
    
    for(char_counter = ZERO_INIT ; char_counter < str_length ; char_counter++ ){
        ret = EUSART_ASYNC_Write_Byte_NonBlocking(_data[char_counter]);
    }
    
    return ret;
}

static void usart_baudrate_calculation(usart_t * _usart_obj ){
    float baudrate_temp = 0 ;
    switch(_usart_obj->baudrate_cfg){
        case BAUDRATE_ASYNC_8BIT_LOW_SPEED :
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN ;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED_BRG ;
                baudrate_temp = ( (_XTAL_FREQ / (float) _usart_obj->baudrate) / 64) - 1 ;
            break;
        case BAUDRATE_ASYNC_8BIT_HIGH_SPEED :
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN ;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED_BRG ;
                baudrate_temp = ( (_XTAL_FREQ / (float) _usart_obj->baudrate) / 16) - 1 ;
            break;
        case BAUDRATE_ASYNC_16BIT_LOW_SPEED :
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN ;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED_BRG ;
                baudrate_temp = ( (_XTAL_FREQ / (float) _usart_obj->baudrate) / 16) - 1 ;
            break;
        case BAUDRATE_ASYNC_16BIT_HIGH_SPEED :
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN ;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED_BRG ;
                baudrate_temp = ( (_XTAL_FREQ / (float) _usart_obj->baudrate) / 4) - 1 ;
            break;
        case BAUDRATE_SYNC_8BIT :
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE ;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN ;
                baudrate_temp = ( (_XTAL_FREQ / (float) _usart_obj->baudrate) / 4) - 1 ;
            break;
        case BAUDRATE_SYNC_16BIT :
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE ;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN ;
                baudrate_temp = ( (_XTAL_FREQ / (float) _usart_obj->baudrate) / 4) - 1 ;
            break;
        default :  
            break;
    }
    SPBRG = (uint8)((uint32)baudrate_temp);
    SPBRGH = (uint8)( ((uint32)baudrate_temp) >> 8) ;
}

static void EUSART_ASYNC_TX_Init(usart_t * _usart_obj){
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _usart_obj->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        /* EUSART Transmit Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _usart_obj->usart_tx_cfg.usart_tx_interrupt_enable){
#if  EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_TX_INTERRUPT_DISABLE();
            EUSART_TX_InterruptHandler = _usart_obj->EUSART_TX_DefaultInterruptHandler ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        if(Interrupt_High_Priority == _usart_obj->usart_tx_cfg.eusart_tx_int_priority){
            EUSART_TX_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{
            EUSART_TX_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        INTERRUPT_PriorityFeatureEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        EUSART_TX_INTERRUPT_ENABLE();
#endif            
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _usart_obj->usart_tx_cfg.usart_tx_interrupt_enable){
            EUSART_TX_INTERRUPT_DISABLE();
        }
        else{  /* Nothing */  }
        /* EUSART 9-BIT Transmit Configuration */
        if(EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == _usart_obj->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == _usart_obj->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
        }
    }
    else{ /* Nothing */ }
}

static void EUSART_ASYNC_RX_Init(usart_t * _usart_obj){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _usart_obj->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE ;
        /* EUSART Receiver Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _usart_obj->usart_rx_cfg.usart_rx_interrupt_enable){
#if  EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_RX_INTERRUPT_DISABLE();
            EUSART_RX_InterruptHandler    = _usart_obj->EUSART_RX_DefaultInterruptHandler ;
            EUSART_FERR_InterruptHandler  = _usart_obj->EUSART_FERR_DefaultInterruptHandler;
            EUSART_OERR_InterruptHandler  = _usart_obj->EUSART_OERR_DefaultInterruptHandler;      
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        if(Interrupt_High_Priority == _usart_obj->usart_rx_cfg.eusart_rx_int_priority){
            EUSART_RX_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{
            EUSART_RX_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        INTERRUPT_PriorityFeatureEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        EUSART_RX_INTERRUPT_ENABLE();
#endif            
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _usart_obj->usart_rx_cfg.usart_rx_interrupt_enable){
            EUSART_RX_INTERRUPT_DISABLE();
        }
        else{  /* Nothing */  }
        /* EUSART 9-BIT Receiver Configuration */
        if(EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == _usart_obj->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == _usart_obj->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
        }
    }
    else{ /* Nothing */ }
}


/* Section: Interrupt Service Routines */

/**
 * @brief EUSART Transmit ISR
 *
 * Handles TX interrupt and calls the user-defined callback if assigned.
 */
void EUSART_TX_ISR(void){
    EUSART_TX_INTERRUPT_DISABLE();
    if(EUSART_TX_InterruptHandler){
        EUSART_TX_InterruptHandler();
    }else{ /* Nothing */ }
}

/**
 * @brief EUSART Receive ISR
 *
 * Handles RX, Framing Error (FERR), and Overrun Error (OERR) interrupts.
 * Calls the user-defined callbacks if assigned.
 */
void EUSART_RX_ISR(void){
    if(EUSART_RX_InterruptHandler){
        EUSART_RX_InterruptHandler();
    }else{ /* Nothing */ }
    if(EUSART_FERR_InterruptHandler){
        EUSART_FERR_InterruptHandler();
    }else{ /* Nothing */ }
    if(EUSART_OERR_InterruptHandler){
        EUSART_OERR_InterruptHandler();
    }else{ /* Nothing */ }
}

