/**
 * @file    I2C_APIs.h
 * @author  Abdelmoniem Ahmed
 * @LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @brief   MSSP I2C Driver Interface for PIC18F4620
 *
 * @details
 * This file contains the public APIs, configuration structures,
 * macros, and data types required to configure and operate the
 * MSSP peripheral in I2C mode.
 *
 * Supported Features:
 *  - I2C Master mode
 *  - I2C Slave mode (7-bit / 10-bit)
 *  - Start / Repeated Start / Stop generation
 *  - ACK / NACK control
 *  - Blocking read/write operations
 *  - Bus collision detection
 *  - Optional interrupt support with callback mechanism
 *
 * Target MCU : PIC18F4620
 * Compiler   : XC8
 * Layer      : MCAL
 */

#ifndef I2C_APIS_H
#define	I2C_APIS_H

/* Section : Includes */

#include"mcal_internal_interrupt.h"
#include"hal_gpio.h"
#include"std_types.h"

/* Section : Macro Declaration */

/* MSSP I2C Enable / Disable */
#define MSSP_I2C_ENABLE                     1
#define MSSP_I2C_DISABLE                    0

/* MSSP I2C Mode Select */
#define MSSP_I2C_MASTER_MODE                1
#define MSSP_I2C_SLAVE_MODE                 0

/* Slew Rate Enable / Disable */
#define I2C_SLEW_RATE_ENABLE_100kHZ         0
#define I2C_SLEW_RATE_DISABLE_400kHZ        1

/* SMBus Enable / Disable */
#define I2C_SMBUS_ENABLE                    1
#define I2C_SMBUS_DISABLE                   0

/* Slave General Call Enable / Disable */
#define I2C_GENERAL_CALL_ENABLE             1
#define I2C_GENERAL_CALL_DISABLE            0

/* Slave Mode Data/Address Indication */
#define I2C_LAST_BYTE_DATA                  1
#define I2C_LAST_BYTE_ADDRESS               0

/* Stop Condition Indication */
#define STOP_CONDITION_DETECTED             1
#define STOP_CONDITION_NOT_DETECTED         0

/* Start Condition Indication */
#define START_CONDITION_DETECTED            1
#define START_CONDITION_NOT_DETECTED        0

/* I2C acknowledge Status (Master Transmit Mode Only) */
#define I2C_ACK_REC_FROM_SLAVE              0
#define I2C_ACK_NOT_REC_FROM_SLAVE          1

/* I2C acknowledge Data Bit (Master Receive Mode Only) */
#define I2C_MASTER_SEND_ACK                 0
#define I2C_MASTER_SEND_NOT_ACK             1

/* I2C acknowledge start (Master Receive mode only) */
#define I2C_MASTER_REC_ACK_START            1
#define I2C_MASTER_REC_NO_SEND_ACK          0xFFU


/* Section : Macro Functions Declarations */

/* MSSP I2C Enable / Disable */
#define MSSP_I2C_ENABLE_CFG()                       ( SSPCON1bits.SSPEN = MSSP_I2C_ENABLE  )
#define MSSP_I2C_DISABLE_CFG()                      ( SSPCON1bits.SSPEN = MSSP_I2C_DISABLE )

/* MSSP I2C Mode Select */
#define MSSP_I2C_MODE_SELECT(MSSP_I2C_Mode_Select)  ( SSPCON1bits.SSPM   = MSSP_I2C_Mode_Select )

/* Slew Rate Enable / Disable */
#define I2C_SLEW_RATE_ENABLE_CFG()                  ( SSPSTATbits.SMP = I2C_SLEW_RATE_ENABLE_100kHZ )
#define I2C_SLEW_RATE_DISABLE_CFG()                 ( SSPSTATbits.SMP = I2C_SLEW_RATE_DISABLE_400kHZ)

/* SMBus Enable / Disable */
#define I2C_SMBUS_ENABLE_CFG()                      ( SSPSTATbits.CKE = I2C_SMBUS_ENABLE )
#define I2C_SMBUS_DISABLE_CFG()                     ( SSPSTATbits.CKE = I2C_SMBUS_DISABLE )

/* General Call Enable / Disable */
#define I2C_GENERAL_CALL_ENABLE_CFG()               ( SSPCON2bits.GCEN = I2C_GENERAL_CALL_ENABLE )
#define I2C_GENERAL_CALL_DISABLE_CFG()              ( SSPCON2bits.GCEN = I2C_GENERAL_CALL_DISABLE )

/* Master Mode Receive Enable / Disable */
#define I2C_MASTER_RECEIVE_ENABLE_CFG()             ( SSPCON2bits.RCEN = 1 )
#define I2C_MASTER_RECEIVE_DISABLE_CFG()            ( SSPCON2bits.RCEN = 0 )

/* Holds clock low (clock stretch) */
#define I2C_CLOCK_STRETCH_ENABLE()                   (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()                  (SSPCON1bits.CKP = 1)  

/* Section : Data Types Declarations */


typedef enum{
    MSSP_I2C_SLAVE_7BIT_ADDR                = 6 ,
    MSSP_I2C_SLAVE_10BIT_ADDR               = 7 ,
    MSSP_I2C_MASTER_MODE_DEFINED_CLK        = 8 ,
    MSSP_I2C_SLAVE_7BIT_ADDR_INT_ENABLE     = 14 ,
    MSSP_I2C_SLAVE_10BIT_ADDR_INT_ENABLE    = 15 ,                        
}MSSP_I2C_Mode_Select;

/**
 * @brief Low-level I2C configuration structure
 *
 * Contains mode configuration parameters used
 * during MSSP I2C initialization.
 */
typedef struct{
    MSSP_I2C_Mode_Select  i2c_mode_cfg ;
    uint8 i2c_slave_address            ; /* I2C Slave Address */
    uint8 i2c_mode                 : 1 ;
    uint8 i2c_slew_rate            : 1 ;
    uint8 i2c_SMBus_Control        : 1 ;
    uint8 i2c_general_call         : 1 ;
    uint8 i2c_master_receive_mode  : 1 ;
    uint8 i2c_reserved             : 3 ;
}i2c_config_t;

/**
 * @brief MSSP I2C high-level configuration structure
 *
 * This structure holds:
 *  - Clock configuration (Master mode)
 *  - Slave address (Slave mode)
 *  - Interrupt configuration
 *  - Bus collision callback
 */
typedef struct{
    uint32 i2c_clock ; /* Master Clock FREQ */
                
                    /* Start Interrupt Configurations */
/* ========================================================= */ 
                    /* Bus Collision Interrupt */
#if         INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE     
    void (* MSSP_I2C_REPORT_WRITE_COLLISION)(void);
#if         INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE    
    INTERRUPT_Priority_cfg mssp_i2c_Bus_COL_int_priority_level ;
#endif    
#endif
/* ========================================================= */ 
                    /* I2C Default Interrupt */    
#if         INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE     
    void (* MSSP_I2C_DEFAULT_INTERRUPT_HANDLER)(void);
    void (* MSSP_I2C_REPORT_RECEIVE_OVERFLOW)(void);
#if         INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE    
    INTERRUPT_Priority_cfg mssp_i2c_int_priority_level ;
#endif
#endif       
/* ========================================================= */    
                /* End Interrupt Configurations */ 
    
    i2c_config_t i2c_cfg ;
    
}mssp_i2c_t;

/*  Section : Function Declarations  */

/**
 * @brief Initialize MSSP peripheral in I2C mode
 *
 * @param i2c_obj Pointer to I2C configuration structure
 *
 * @return Std_ReturnType
 *         - E_OK     : Initialization successful
 *         - E_NOT_OK : Null pointer or invalid configuration
 *
 * @note
 * This function configures:
 *  - Master or Slave mode
 *  - Clock frequency (Master mode)
 *  - Slave address (Slave mode)
 *  - Slew rate
 *  - SMBus control
 *  - Interrupt settings (if enabled)
 */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t * i2c_obj);

/**
 * @brief Deinitialize MSSP I2C module
 *
 * @param i2c_obj Pointer to I2C configuration structure
 *
 * @return Std_ReturnType
 *
 * @note
 * Disables MSSP module and associated interrupts.
 */
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t * i2c_obj);

/**
 * @brief Generate Start condition on I2C bus (Master mode)
 *
 * @param i2c_obj Pointer to I2C configuration structure
 *
 * @return Std_ReturnType
 *
 * @note
 * Blocks until Start condition is completed by hardware.
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t * i2c_obj);

/**
 * @brief Generate Repeated Start condition (Master mode)
 *
 * @param i2c_obj Pointer to I2C configuration structure
 *
 * @return Std_ReturnType
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t * i2c_obj);

/**
 * @brief Generate Stop condition on I2C bus (Master mode)
 *
 * @param i2c_obj Pointer to I2C configuration structure
 *
 * @return Std_ReturnType
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t * i2c_obj);

/**
 * @brief Transmit one byte over I2C bus (Blocking mode)
 *
 * @param i2c_obj Pointer to I2C configuration structure
 * @param i2c_data Data byte to transmit
 * @param _ack Pointer to store acknowledge status
 *
 * @return Std_ReturnType
 *
 * @note
 * Function waits until transmission is complete.
 * ACK status is stored in `_ack`.
 */
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t * i2c_obj , uint8 i2c_data , uint8 *_ack);

/**
 * @brief Receive one byte from I2C bus (Blocking mode)
 *
 * @param i2c_obj Pointer to I2C configuration structure
 * @param ack Acknowledge selection (ACK / NACK)
 * @param i2c_data Pointer to store received byte
 *
 * @return Std_ReturnType
 *
 * @note
 * After reading, the master sends ACK or NACK
 * depending on the `ack` parameter.
 */
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t * i2c_obj , uint8 ack ,uint8 * i2c_data);


#endif	/* I2C_APIS_H */

