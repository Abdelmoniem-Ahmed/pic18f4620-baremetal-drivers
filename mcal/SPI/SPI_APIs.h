/**
 * @file SPI_APIs.h
 * @brief MSSP SPI Driver Interface for PIC18F4620
 *
 * @details
 * This file contains the public interface for the MSSP (Master Synchronous
 * Serial Port) module configured in SPI mode for the PIC18F4620 microcontroller.
 *
 * The driver supports:
 *  - SPI Master mode
 *  - SPI Slave mode
 *  - Configurable clock polarity (CKP)
 *  - Configurable clock edge (CKE)
 *  - Master sampling control (SMP)
 *  - Interrupt-driven communication (optional)
 *
 * Designed following:
 *  - Bare-metal embedded systems best practices
 *  - MCAL layered architecture
 *  - Configurable compile-time interrupt support
 *
 * @author  Abdelmoniem Ahmed
 *
 * @note Requires MPLAB XC8 compiler.
 * @note Requires proper oscillator configuration before SPI initialization.
 *
 * Layer  : MCAL (Microcontroller Abstraction Layer)
 * Target : PIC18F4620
 *
 * LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * 
 */

#ifndef SPI_APIS_H
#define	SPI_APIS_H

/* Section : Includes */

#include"mcal_internal_interrupt.h"
#include"hal_gpio.h"
#include"std_types.h"

/* Section : Macro Declaration */

/**
 * SPI Clock Polarity Configuration (CKP)
 */
#define SPI_CLK_POL_IDLE_HIGH_CFG                   1
#define SPI_CLK_POL_IDLE_LOW_CFG                    0

/**
 * SPI Clock Edge Configuration (CKE)
 */
#define SPI_CLKE_TRANSMISSION_ACTIVE_TO_IDLE_CFG    1
#define SPI_CLKE_TRANSMISSION_IDLE_TO_ACTIVE_CFG    0

/**
 * SPI Module Enable/Disable
 */
#define SPI_MODULE_ENABLE_CFG                       1
#define SPI_MODULE_DISABLE_CFG                      0   

/**
 * SPI Status Flags
 */
#define SPI_WRITE_COLLISION_OCCUR_CFG               1
#define SPI_CLEAR_WRCOL_BIT_CFG                     0

#define SPI_OVERFLOW_OCCUR_CFG                      1
#define SPI_CLEAR_OVERFLOW_BIT_CFG                  0

#define SPI_RECEIVE_MODE_BUFFER_FULL_CFG            1

/**
 * SPI Sampling Control (Master Mode Only)
 */
#define SPI_MASTER_SAMPLE_AT_END_CFG                1
#define SPI_MASTER_SAMPLE_AT_MIDDLE_CFG             0
#define SPI_SLAVE_SAMPLE_MUST_CLEARED_CFG           0

/**
 * SPI Transmit/Receive Enable
 */
#define SPI_TRANSMIT_ENABLE_CFG                     1
#define SPI_TRANSMIT_DISABLE_CFG                    0

#define SPI_RECEIVE_ENABLE_CFG                      1
#define SPI_RECEIVE_DISABLE_CFG                     0


/* Section : Macro Functions Declarations */

/**
 * @brief Enable MSSP SPI module.
 */
#define MSSP_SPI_ENABLE()                               (SSPCON1bits.SSPEN = SPI_MODULE_ENABLE_CFG)
/**
 * @brief Disable MSSP SPI module.
 */
#define MSSP_SPI_DISABLE()                              (SSPCON1bits.SSPEN = SPI_MODULE_DISABLE_CFG)

/**
 * @brief Configure clock polarity.
 */
#define MSSP_SPI_CLK_POL_HIGH()                         (SSPCON1bits.CKP = SPI_CLK_POL_IDLE_HIGH_CFG)
#define MSSP_SPI_CLK_POL_LOW()                          (SSPCON1bits.CKP = SPI_CLK_POL_IDLE_LOW_CFG)

/**
 * @brief Select SPI operating mode (Master/Slave with clock selection).
 */
#define MSSP_SPI_MODE_SELECT(_x)                        (SSPCON1bits.SSPM = _x)

/**
 * @brief Select transmit edge.
 */
#define MSSP_SPI_EDGE_FROM_ACTIVE_TO_IDLE_SELECT()      (SSPSTATbits.CKE = SPI_CLKE_TRANSMISSION_ACTIVE_TO_IDLE_CFG)
#define MSSP_SPI_EDGE_FROM_IDEL_TO_ACTIVE_SELECT()      (SSPSTATbits.CKE = SPI_CLKE_TRANSMISSION_IDLE_TO_ACTIVE_CFG)

/**
 * @brief Configure sampling time (Master mode only).
 */
#define MSSP_SPI_MASTER_SAMPLE_TIME_AT_END_SELECT()     (SSPSTATbits.SMP = SPI_MASTER_SAMPLE_AT_END_CFG )
#define MSSP_SPI_MASTER_SAMPLE_TIME_AT_MIDDLE_SELECT()  (SSPSTATbits.SMP = SPI_MASTER_SAMPLE_AT_MIDDLE_CFG )

#define MSSP_SPI_SLAVE_SAMPLE_TIME_MUST_CLEAR()         (SSPSTATbits.SMP = SPI_SLAVE_SAMPLE_MUST_CLEARED_CFG)   

/**
 * @brief Check if write collision occurred.
 * @return 1 if collision occurred, otherwise 0.
 */
#define MSSP_SPI_IS_WRITE_COLLISION_OCCUR()             (SPI_WRITE_COLLISION_OCCUR_CFG == SSPCON1bits.WCOL)

/**
 * @brief Check if overflow occurred.
 * @return 1 if overflow occurred, otherwise 0.
 */
#define MSSP_SPI_IS_OVERFLOW_OCCUR()                    (SPI_OVERFLOW_OCCUR_CFG == SSPCON1bits.SSPOV)

/**
 * @brief Clear write collision flag.
 */
#define MSSP_SPI_WRITE_COLLISION_CLEAR()                (SSPCON1bits.WCOL = SPI_CLEAR_WRCOL_BIT_CFG)

/**
 * @brief Clear overflow flag.
 */
#define MSSP_SPI_OVERFLOW_CLEAR()                       (SSPCON1bits.SSPOV = SPI_CLEAR_OVERFLOW_BIT_CFG)

/**
 * @brief Check if buffer register is full.
 * @return 1 if buffer full, otherwise 0.
 */
#define MSSP_SPI_IS_BUF_REG_FULL()                      (SSPSTATbits.BF)


/* Section : Data Types Declarations */

/**
 * @enum SPI_Modes_Select_t
 * @brief MSSP SPI operating modes.
 */
typedef enum{
    SPI_Master_CLK_FOSC_DIV4 ,
    SPI_Master_CLK_FOSC_DIV16 ,
    SPI_Master_CLK_FOSC_DIV64 ,
    SPI_Master_CLK_FTMR2_DIV2 ,
    SPI_Slave_Slave_Select_Enable ,
    SPI_Slave_Slave_Select_Disable         
}SPI_Modes_Select_t;

/**
 * @struct mssp_spi_t
 * @brief MSSP SPI configuration structure.
 *
 * This structure is used to configure the SPI peripheral before initialization.
 */
typedef struct{
#if         INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_DefaultInterruptHandler) (void);
#if         INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE  
    INTERRUPT_Priority_cfg mssp_spi_int_priority_level ;
#endif
#endif 
//    master select slave to communicate with using pins like this
//    the one desired to transmit/receive must its pin be logic 0
//    pin_config_t slave_select_pins_according_to_slave_numbers ;
    SPI_Modes_Select_t spi_master_slave_select ;
    uint8 spi_transmit_enable                   : 1 ;
    uint8 spi_receive_enable                    : 1 ;
    uint8 spi_clock_polarity_select             : 1 ;
    uint8 spi_clock_transmit_edge_select        : 1 ;
    uint8 spi_master_sample_at_select           : 1 ;
    
}mssp_spi_t;

/* Section : Function Declarations */

/**
 * @brief Initialize the MSSP module in SPI mode.
 *
 * @param spi_obj Pointer to SPI configuration structure.
 * @return Std_ReturnType
 *         - E_OK  : Initialization successful
 *         - E_NOT_OK : Initialization failed
 */
Std_ReturnType MSSP_SPI_Init(mssp_spi_t *spi_obj);

/**
 * @brief Deinitialize the MSSP SPI module.
 *
 * @param spi_obj Pointer to SPI configuration structure.
 * @return Std_ReturnType
 */
Std_ReturnType MSSP_SPI_DeInit(mssp_spi_t *spi_obj);

/**
 * @brief Transmit one byte and receive one byte simultaneously.
 *
 * @param data_transmit  Byte to transmit.
 * @param data_received  Pointer to store received byte.
 *
 * @return Std_ReturnType
 */
Std_ReturnType MSSP_SPI_Transmit_Receive_Byte(uint8 data_transmit , uint8 * data_received);


#endif	/* SPI_APIS_H */

