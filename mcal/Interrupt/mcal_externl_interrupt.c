/**
 * @file    mcal_externl_interrupt.c
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/Abdelmoniem-Ahmed/
 * @brief   External Interrupt Driver Implementation
 * @details This file contains the implementation of external interrupt
 *          services for PIC microcontrollers.
 *
 *          Supported interrupt sources:
 *          - INT0, INT1, INT2 external interrupts
 *          - PORTB change interrupts (RB4?RB7)
 *
 *          Features:
 *          - Configurable edge triggering (INTx)
 *          - Optional interrupt priority support
 *          - GPIO pin initialization
 *          - User-defined callback functions
 *
 *          The ISR functions defined here are called from the central
 *          interrupt manager.
 */

#include "mcal_externl_interrupt.h"

/* ----------------------------------------------------
 * Section : Static Callback Function Pointers
 * ----------------------------------------------------
 */

/* INTx Interrupt Callbacks */
static void (* INT0_InterruptHandler ) (void) = NULL;
static void (* INT1_InterruptHandler ) (void) = NULL;
static void (* INT2_InterruptHandler ) (void) = NULL;

/* PORTB Change Interrupt Callbacks */
static void (* RB4_InterruptHandler_High ) (void) = NULL;
static void (* RB4_InterruptHandler_Low ) (void) = NULL;
static void (* RB5_InterruptHandler_High ) (void) = NULL;
static void (* RB5_InterruptHandler_Low ) (void) = NULL;
static void (* RB6_InterruptHandler_High ) (void) = NULL;
static void (* RB6_InterruptHandler_Low ) (void) = NULL;
static void (* RB7_InterruptHandler_High ) (void) = NULL;
static void (* RB7_InterruptHandler_Low ) (void) = NULL;

/* ----------------------------------------------------
 * Section : Static Helper Function Declarations
 * ----------------------------------------------------
 */

/* INTx internal helpers */
static Std_ReturnType INT0_SetInterruptHandler(void (* InterruptHandler ) (void));
static Std_ReturnType INT1_SetInterruptHandler(void (* InterruptHandler ) (void));
static Std_ReturnType INT2_SetInterruptHandler(void (* InterruptHandler ) (void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const Interrupt_INTx_t * interrupt_obj);

static Std_ReturnType Interrupt_INTx_Enable (const Interrupt_INTx_t * interrupt_obj);
static Std_ReturnType Interrupt_INTx_Disable (const Interrupt_INTx_t * interrupt_obj);

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_PRIORITY_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init (const Interrupt_INTx_t * interrupt_obj);
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init (const Interrupt_INTx_t * interrupt_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init (const Interrupt_INTx_t * interrupt_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag (const Interrupt_INTx_t * interrupt_obj);

/* RBx internal helpers */
static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const Interrupt_RBx_t * interrupt_obj);
static Std_ReturnType Interrupt_RBx_Enable (const Interrupt_RBx_t * interrupt_obj);
static Std_ReturnType Interrupt_RBx_Disable (const Interrupt_RBx_t * interrupt_obj);

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_PRIORITY_ENABLE
static Std_ReturnType Interrupt_RBx_Priority_Init (const Interrupt_RBx_t * interrupt_obj);
#endif

static Std_ReturnType Interrupt_RBx_Pin_Init (const Interrupt_RBx_t * interrupt_obj);


/* ----------------------------------------------------
 * Section : INTx Public APIs
 * ----------------------------------------------------
 */

/**
 * @brief Initialize an INTx external interrupt
 */
Std_ReturnType interrupt_INTx_Init(const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the External Interrupt */
        ret = Interrupt_INTx_Disable(interrupt_obj);
        /* configure the interrupt triggering edge rising/falling */
        ret = Interrupt_INTx_Edge_Init(interrupt_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* Configuring The Interrupt Priority Level High/Low */
        ret = Interrupt_INTx_Priority_Init(interrupt_obj);
        INTERRUPT_PriorityFeatureEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        /* Configure the external interrupt I/O pin */  
        ret = Interrupt_INTx_Pin_Init(interrupt_obj);
        /* Configure default interrupt call back */
        ret = Interrupt_INTx_SetInterruptHandler(interrupt_obj);
        /* Clear the interrupt flag */
        ret = Interrupt_INTx_Clear_Flag(interrupt_obj);
        /* Enable the External Interrupt */
        ret = Interrupt_INTx_Enable(interrupt_obj);
    }
    return ret;
}

/**
 * @brief Deinitialize an INTx interrupt
 */
Std_ReturnType interrupt_INTx_DeInit(const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(interrupt_obj);
    }
    return ret;
}

/* ----------------------------------------------------
 * Section : RBx Public APIs
 * ----------------------------------------------------
 */

/**
 * @brief Initialize PORTB change interrupt (RB4?RB7)
 */
Std_ReturnType interrupt_RBx_Init(const Interrupt_RBx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        /* THIS Function Will DISABLE INTERRUPT FEATURE FOR RBx */
        EXTERNAL_INTERRUPTS_RBx_DISABLE();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityFeatureEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        if( Interrupt_High_Priority == interrupt_obj->priority) { EXTERNAL_INTERRUPT_RBx_HIGH_PRIORITY(); }
        else if(Interrupt_Low_Priority == interrupt_obj->priority) { EXTERNAL_INTERRUPT_RBx_LOW_PRIORITY(); }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        /* THIS Function Will CLEAR FLAG FOR RBx */
        EXTERNAL_INTERRUPTS_RBx_CLEAR_FLAG();
        /* This Function Will Initialize Pin As Input */
        ret = gpio_pin_direction_initialize(&(interrupt_obj->mcu_pin));
        /* This Function Will Set the ISR Pointer */
        ret = Interrupt_RBx_SetInterruptHandler(interrupt_obj);
        /* THIS Function Will ENABLE INTERRUPT FEATURE FOR RBx */
        EXTERNAL_INTERRUPTS_RBx_ENABLE();
    }
    return ret;
}

/**
 * @brief Deinitialize RBx interrupt
 */
Std_ReturnType interrupt_RBx_DeInit(const Interrupt_RBx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_RBx_Disable(interrupt_obj);
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Enable (const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->source){
        case  Interrupt_INT0 :           
            EXTERNAL_INTERRUPT_INT0_ENABLE();
            break;
        case  Interrupt_INT1 :  
            EXTERNAL_INTERRUPT_INT1_ENABLE();      break;
        case  Interrupt_INT2 : 
            EXTERNAL_INTERRUPT_INT2_ENABLE();     break;
        default : ret = E_NOT_OK;
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Disable (const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->source){
        case  Interrupt_INT0 :  EXTERNAL_INTERRUPT_INT0_DISABLE();     break;
        case  Interrupt_INT1 :  EXTERNAL_INTERRUPT_INT1_DISABLE();      break;
        case  Interrupt_INT2 :  EXTERNAL_INTERRUPT_INT2_DISABLE();     break;
        default : ret = E_NOT_OK;
    }
    return ret;
}


static Std_ReturnType Interrupt_INTx_Edge_Init (const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->source){
        case  Interrupt_INT0 :  
            if(Interrupt_Falling_Edge == interrupt_obj->edge){
                EXTERNAL_INTERRUPT_INT0_SET_FALLING_EDGE();
            }
            else if(Interrupt_Rising_Edge == interrupt_obj->edge){
                EXTERNAL_INTERRUPT_INT0_SET_RISING_EDGE();
            } break;
        case  Interrupt_INT1 :  
            if(Interrupt_Falling_Edge == interrupt_obj->edge){
                EXTERNAL_INTERRUPT_INT1_SET_FALLING_EDGE();
            }
            else if(Interrupt_Rising_Edge == interrupt_obj->edge){
                EXTERNAL_INTERRUPT_INT1_SET_RISING_EDGE();
            } break;
        case  Interrupt_INT2 :
            if(Interrupt_Falling_Edge == interrupt_obj->edge){
                EXTERNAL_INTERRUPT_INT2_SET_FALLING_EDGE();
            }
            else if(Interrupt_Rising_Edge == interrupt_obj->edge){
                EXTERNAL_INTERRUPT_INT2_SET_RISING_EDGE();
            } break;
        default : ret = E_NOT_OK;
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Pin_Init (const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_pin_direction_initialize(&(interrupt_obj->mcu_pin));
    
    return ret;
}


static Std_ReturnType Interrupt_INTx_Clear_Flag (const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->source){
        case  Interrupt_INT0 :  EXTERNAL_INTERRUPT_INT0_CLEAR_FLAG();     break;
        case  Interrupt_INT1 :  EXTERNAL_INTERRUPT_INT1_CLEAR_FLAG();      break;
        case  Interrupt_INT2 :  EXTERNAL_INTERRUPT_INT2_CLEAR_FLAG();     break;
        default : ret = E_NOT_OK;
    }
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType Interrupt_INTx_Priority_Init (const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->source){
        case  Interrupt_INT1 :  
            if(Interrupt_High_Priority == interrupt_obj->priority){
                EXTERNAL_INTERRUPT_INT1_HIGH_PRIORITY();
            }
            else if(Interrupt_Low_Priority == interrupt_obj->priority){
                EXTERNAL_INTERRUPT_INT1_LOW_PRIORITY();
            }
            break;
        case  Interrupt_INT2 :
            if(Interrupt_High_Priority == interrupt_obj->priority){
                EXTERNAL_INTERRUPT_INT2_HIGH_PRIORITY();
            }
            else if(Interrupt_Low_Priority == interrupt_obj->priority){
                EXTERNAL_INTERRUPT_INT2_LOW_PRIORITY();
            } 
            break;
        default : ret = E_NOT_OK;
    }
    return ret;
}


#endif

static Std_ReturnType INT0_SetInterruptHandler(void (* InterruptHandler ) (void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (* InterruptHandler ) (void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (* InterruptHandler ) (void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const Interrupt_INTx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->source){
        case  Interrupt_INT0 : INT0_SetInterruptHandler(interrupt_obj->External_InterruptHandler);      break;
        case  Interrupt_INT1 : INT1_SetInterruptHandler(interrupt_obj->External_InterruptHandler);      break;
        case  Interrupt_INT2 : INT2_SetInterruptHandler(interrupt_obj->External_InterruptHandler);      break;
        default : ret = E_NOT_OK;
    }
    return ret;
}


static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const Interrupt_RBx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    switch(interrupt_obj->mcu_pin.pin){
        case  PIN4 : 
            RB4_InterruptHandler_High = interrupt_obj->External_InterruptHandler_High;
            RB4_InterruptHandler_Low = interrupt_obj->External_InterruptHandler_Low;    break;
        case  PIN5 : 
            RB5_InterruptHandler_High = interrupt_obj->External_InterruptHandler_High;
            RB5_InterruptHandler_Low = interrupt_obj->External_InterruptHandler_Low;    break; 
        case  PIN6 : 
            RB6_InterruptHandler_High = interrupt_obj->External_InterruptHandler_High;
            RB6_InterruptHandler_Low = interrupt_obj->External_InterruptHandler_Low;    break;
        case  PIN7 : 
            RB7_InterruptHandler_High = interrupt_obj->External_InterruptHandler_High;
            RB7_InterruptHandler_Low = interrupt_obj->External_InterruptHandler_Low;    break;
        default : ret = E_NOT_OK;
    }
    return ret;
}


Std_ReturnType Interrupt_RBx_Disable (const Interrupt_RBx_t * interrupt_obj){
    Std_ReturnType ret = E_OK;
    EXTERNAL_INTERRUPTS_RBx_DISABLE();
    return ret;
}

/* ----------------------------------------------------
 * Section : ISR Implementations
 * ----------------------------------------------------
 */

/**
 * @brief INT0 Interrupt Service Routine
 */
void INT0_ISR(void){
    /* The INT0 External Interrupt occured "the flag must be cleared in software" */
    EXTERNAL_INTERRUPT_INT0_CLEAR_FLAG();
    /* Code : To Be Executed from mcal Interrupt Context */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    
}

/**
 * @brief INT1 Interrupt Service Routine
 */
void INT1_ISR(void){
    /* The INT1 External Interrupt occured "the flag must be cleared in software" */
    EXTERNAL_INTERRUPT_INT1_CLEAR_FLAG();
    /* Code */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    
}

/**
 * @brief INT2 Interrupt Service Routine
 */
void INT2_ISR(void){
    /* The INT2 External Interrupt occured "the flag must be cleared in software" */
    EXTERNAL_INTERRUPT_INT2_CLEAR_FLAG();
    /* Code */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    
}

/**
 * @brief RB4 Change Interrupt Service Routine
 */
void RB4_ISR(uint8 source){
    /* THIS Function Will CLEAR FLAG FOR RBx */
    EXTERNAL_INTERRUPTS_RBx_CLEAR_FLAG();
    /* Code must be executed for context switch */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if( (RB4_InterruptHandler_High) && (1 == source ))
    { RB4_InterruptHandler_High(); }
    else if((RB4_InterruptHandler_Low) && (0 == source ))
    { RB4_InterruptHandler_Low(); }
    
}

/**
 * @brief RB5 Change Interrupt Service Routine
 */
void RB5_ISR(uint8 source){
    /* THIS Function Will CLEAR FLAG FOR RBx */
    EXTERNAL_INTERRUPTS_RBx_CLEAR_FLAG();
    /* Code must be executed for context switch */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if( (RB5_InterruptHandler_High) && (1 == source ))
    { RB5_InterruptHandler_High(); }
    else if ((RB5_InterruptHandler_Low) && (0 == source ))
    { RB5_InterruptHandler_Low(); }   
}

/**
 * @brief RB6 Change Interrupt Service Routine
 */
void RB6_ISR(uint8 source){
    /* THIS Function Will CLEAR FLAG FOR RBx */
    EXTERNAL_INTERRUPTS_RBx_CLEAR_FLAG();
    /* Code must be executed for context switch */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if( (RB6_InterruptHandler_High) && (1 == source ))
    { RB6_InterruptHandler_High(); }
    else if ((RB6_InterruptHandler_Low) && (0 == source ))
    { RB6_InterruptHandler_Low(); }
}

/**
 * @brief RB7 Change Interrupt Service Routine
 */
void RB7_ISR(uint8 source){
    /* THIS Function Will CLEAR FLAG FOR RBx */
    EXTERNAL_INTERRUPTS_RBx_CLEAR_FLAG();
    /* Code must be executed for context switch */
    
    /* Callback Function Gets Called Every Time this ISR executes */
    if( (RB7_InterruptHandler_High) && (1 == source ))
    { RB7_InterruptHandler_High(); }
    else if ((RB7_InterruptHandler_Low) && (0 == source ))
    { RB7_InterruptHandler_Low(); }
    
}


