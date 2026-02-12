/**
 * hal_eusart PIC18F4620
 *
 * Overview:
 * This driver provides a clean and configurable MCAL interface for the 
 * EUSART (Enhanced Universal Synchronous Asynchronous Receiver Transmitter) 
 * peripheral of the PIC18F4620 microcontroller.
 *
 * Features:
 * - Asynchronous and synchronous modes
 * - 8-bit and 16-bit baud rate generation
 * - High-speed/low-speed asynchronous modes
 * - 9-bit data transmission and reception
 * - Interrupt-driven TX/RX handling
 * - Framing and overrun error detection
 *
 * Design follows:
 * - Bare-metal embedded best practices
 * - MCAL layering
 *
 * Author: Abdelmoniem Ahmed
 * LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
 */

#ifndef HAL_EUSART_H
#define	HAL_EUSART_H

/* Section : Includes */

#include"mcal_internal_interrupt.h"
#include"hal_gpio.h"
#include"std_types.h"

/* Section : Macro Declaration */

/* EUSART Module Control */
#define EUSART_ENABLE                               1
#define EUSART_DISABLE                              0

/* Mode Selection */
#define EUSART_SYNCHRONOUS_MODE                     1
#define EUSART_ASYNCHRONOUS_MODE                    0

/* Asynchronous Speed */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED_BRG          1
#define EUSART_ASYNCHRONOUS_LOW_SPEED_BRG           0

/* Baud Rate Generator Width */
#define EUSART_16BIT_BAUDRATE_GEN                   1
#define EUSART_8BIT_BAUDRATE_GEN                    0

/* TX Control */
#define EUSART_ASYNCHRONOUS_TX_ENABLE               1
#define EUSART_ASYNCHRONOUS_TX_DISABLE              0

#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE    0

#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE         0

/* RX Control */
#define EUSART_ASYNCHRONOUS_RX_ENABLE               1
#define EUSART_ASYNCHRONOUS_RX_DISABLE              0

#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE    0

#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE         0

/* Error Status */
#define EUSART_FRAMING_ERROR_DETECTED               1
#define EUSART_FRAMING_ERROR_CLEARED                0

#define EUSART_OVERRUN_ERROR_DETECTED               1
#define EUSART_OVERRUN_ERROR_CLEARED                0

/* Section : Macro Functions Declarations */


/* Section : Data Types Declarations */

/**
 * @brief EUSART Baud Rate Generator Configuration
 *
 * This enumeration defines the possible configurations for baud rate generation
 * depending on asynchronous/synchronous mode, 8-bit/16-bit width, and speed.
 */
typedef enum{
    BAUDRATE_ASYNC_8BIT_LOW_SPEED ,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED ,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED ,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED ,
    BAUDRATE_SYNC_8BIT ,
    BAUDRATE_SYNC_16BIT        
}baudrate_gen_t;

/**
 * @brief EUSART Transmitter Configuration
 *
 * This struct configures the EUSART transmitter functionality.
 * It supports enabling TX, 9-bit transmission, and TX interrupts.
 */
typedef struct{
    INTERRUPT_Priority_cfg eusart_tx_int_priority;
    uint8 usart_tx_enable : 1 ;
    uint8 usart_tx_9bit_enable : 1 ;
    uint8 usart_tx_interrupt_enable : 1 ;
    uint8 usart_tx_reserved : 5 ;
}usart_tx_cfg_t;

/**
 * @brief EUSART Receiver Configuration
 *
 * This struct configures the EUSART receiver functionality.
 * It supports enabling RX, 9-bit reception, and RX interrupts.
 */
typedef struct{
    INTERRUPT_Priority_cfg eusart_rx_int_priority;
    uint8 usart_rx_enable : 1 ;
    uint8 usart_rx_9bit_enable : 1 ;
    uint8 usart_rx_interrupt_enable : 1 ;
    uint8 usart_rx_reserved : 5 ;
}usart_rx_cfg_t;

/**
 * @brief EUSART Error Status
 *
 * This union represents the status of EUSART errors.
 * It provides both bit-level flags and a combined byte access.
 */
typedef union{
    struct{
        uint8 usart_frame_error_ferr   : 1 ;
        uint8 usart_overrun_error_oerr : 1 ;
        uint8 usart_error_reserved : 6 ;
    };
    uint8 error_status ;
}usart_error_status_t;

/**
 * @brief EUSART Configuration Object
 *
 * This struct holds the complete configuration for the EUSART peripheral,
 * including baud rate, TX/RX configuration, error handlers, and interrupt callbacks.
 */
typedef struct{
    uint32 baudrate ;
    baudrate_gen_t baudrate_cfg ;
    usart_tx_cfg_t usart_tx_cfg ;
    usart_rx_cfg_t usart_rx_cfg ;
    usart_error_status_t error_status ;
    void (* EUSART_TX_DefaultInterruptHandler)(void);
    void (* EUSART_RX_DefaultInterruptHandler)(void);
    void (* EUSART_FERR_DefaultInterruptHandler)(void);
    void (* EUSART_OERR_DefaultInterruptHandler)(void);
}usart_t;

/* Section : Function Declarations */

/* Section: Function Declarations */

/**
 * @brief Initializes the EUSART peripheral in asynchronous mode.
 *
 * Configures baud rate, transmitter, receiver, and interrupt settings
 * according to the provided `usart_t` configuration object.
 *
 * @param _usart_obj Pointer to a `usart_t` object containing configuration parameters.
 *
 * @return Std_ReturnType
 * - E_OK: Initialization successful
 * - E_NOT_OK: Initialization failed
 */
Std_ReturnType EUSART_ASYNC_Init(usart_t * _usart_obj);

/**
 * @brief De-initializes the EUSART peripheral.
 *
 * Disables the transmitter, receiver, and associated interrupts.
 * Clears error flags and resets configuration registers to default state.
 *
 * @param _usart_obj Pointer to a `usart_t` object associated with the EUSART peripheral.
 *
 * @return Std_ReturnType
 * - E_OK: De-initialization successful
 * - E_NOT_OK: De-initialization failed
 */
Std_ReturnType EUSART_ASYNC_DeInit(usart_t * _usart_obj);

/**
 * @brief Reads a single byte from the EUSART in blocking mode.
 *
 * Waits until a byte is received, then returns it.
 *
 * @param _data Pointer to store the received byte.
 *
 * @return Std_ReturnType
 * - E_OK: Byte successfully received
 * - E_NOT_OK: Read failed or error occurred
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(uint8 *_data);

/**
 * @brief Reads a single byte from the EUSART in non-blocking mode.
 *
 * Returns immediately. If data is available, it is stored in `_data`.
 * Otherwise, the function returns an error.
 *
 * @param _data Pointer to store the received byte.
 *
 * @return Std_ReturnType
 * - E_OK: Byte successfully received
 * - E_NOT_OK: No data available or error occurred
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_NonBlocking(uint8 *_data);

/**
 * @brief Writes a single byte to the EUSART in blocking mode.
 *
 * Waits until the transmitter is ready, then sends the byte.
 *
 * @param _data Byte to transmit.
 *
 * @return Std_ReturnType
 * - E_OK: Byte successfully transmitted
 * - E_NOT_OK: Transmission failed
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(uint8 _data);

/**
 * @brief Writes a string of bytes to the EUSART in blocking mode.
 *
 * Transmits each byte in `_data` sequentially. Waits for the transmitter
 * to be ready before sending each byte.
 *
 * @param _data Pointer to the array of bytes (string) to transmit.
 * @param str_length Length of the string/array to transmit.
 *
 * @return Std_ReturnType
 * - E_OK: String successfully transmitted
 * - E_NOT_OK: Transmission failed
 */
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(uint8 *_data , uint16 str_length);

/**
 * @brief Writes a single byte to the EUSART in non-blocking mode.
 *
 * Returns immediately. If the transmitter is ready, the byte is sent.
 * Otherwise, the function returns an error.
 *
 * @param _data Byte to transmit.
 *
 * @return Std_ReturnType
 * - E_OK: Byte successfully transmitted
 * - E_NOT_OK: Transmitter not ready
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_NonBlocking(uint8 _data);

/**
 * @brief Writes a string of bytes to the EUSART in non-blocking mode.
 *
 * Transmits each byte in `_data` sequentially if the transmitter is ready.
 * Returns an error if the transmitter is busy at any point.
 *
 * @param _data Pointer to the array of bytes (string) to transmit.
 * @param str_length Length of the string/array to transmit.
 *
 * @return Std_ReturnType
 * - E_OK: String successfully transmitted
 * - E_NOT_OK: Transmission failed due to busy transmitter
 */
Std_ReturnType EUSART_ASYNC_Write_String_NonBlocking(uint8 *_data , uint16 str_length);


#endif	/* HAL_EUSART_H */
