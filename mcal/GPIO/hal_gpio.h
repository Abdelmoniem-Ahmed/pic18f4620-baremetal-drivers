/**
 * @file hal_gpio.h
 * @brief GPIO HAL driver header file for PIC18F4620.
 *
 * This file provides the public interface for GPIO pin-level
 * and port-level configuration and control.
 *
 * The driver abstracts direct register access and is intended
 * to be used by application code and ECUAL drivers.
 *
 * @author Abdelmoniem Ahmed
 * @linkedin <- https://www.linkedin.com/in/abdelmoniem-ahmed/ ->
 * @date 2026
 */

/**
 * @defgroup GPIO_Driver GPIO HAL Driver
 * @{
 *
 * @brief
 * This module provides APIs to configure and control GPIO pins and ports
 * for the PIC18F4620 microcontroller.
 *
 * Features:
 * - Pin direction configuration
 * - Pin logic read/write/toggle
 * - Port-level configuration and access
 *
 * Notes:
 * - This driver is MCU-specific (PIC18F4620).
 * - ECUAL drivers must use this API instead of direct register access.
 *
 * @}
 */



#ifndef HAL_GPIO_H
#define	HAL_GPIO_H




/* Section : Includes */

#include <xc.h>
#include"std_libraries.h"
#include"std_types.h"
#include"hal_gpio_cfg.h"
#include"device_config.h"

/* Section : Macro Declaration */

/**
 * @brief Bit mask used for bit manipulation.
 */
#define BIT_MASK                           (uint8)0x01

/**
 * @brief Maximum number of pins per GPIO port.
 */
#define PORT_PIN_MAX_NUMBER                8

/**
 * @brief Total number of GPIO ports supported.
 */
#define PORT_MAX_NUMBER                    5

/**
 * @brief Mask used for port-level toggle operations.
 */
#define PORT_MASK                          0xFF

/* Section : Macro Functions Declarations */


/**
 * @brief Access an 8-bit hardware register.
 *
 * @param _X Register address.
 */
#define HWREG8(_X)                         ( *((volatile uint8 *)(_X)) )

/**
 * @brief Set a specific bit in a register.
 *
 * @param REG Register to modify.
 * @param BIT_POSN Bit position.
 */
#define SET_BIT(REG , BIT_POSN)            (REG |=  (BIT_MASK << BIT_POSN) )

/**
 * @brief Clear a specific bit in a register.
 *
 * @param REG Register to modify.
 * @param BIT_POSN Bit position.
 */
#define CLEAR_BIT(REG , BIT_POSN)          (REG &= ~(BIT_MASK << BIT_POSN) )

/**
 * @brief Toggle a specific bit in a register.
 *
 * @param REG Register to modify.
 * @param BIT_POSN Bit position.
 */
#define TOGGLE_BIT(REG , BIT_POSN)         (REG ^=  (BIT_MASK << BIT_POSN) )

/**
 * @brief Read the value of a specific bit in a register.
 *
 * @param REG Register to read from.
 * @param BIT_POSN Bit position.
 *
 * @return Bit value (0 or 1).
 */
#define READ_BIT(REG , BIT_POSN)           ( (REG >> BIT_POSN) & BIT_MASK  )

/* Section : Data Types Declarations */


/**
 * @enum Logic_t
 * @brief GPIO logic level.
 */
typedef enum{
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH         
}Logic_t;

/**
 * @enum direction_t
 * @brief GPIO pin direction.
 */
typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT        
}direction_t;

/**
 * @enum pin_index_t
 * @brief GPIO pin number.
 */
typedef enum{
    PIN0 = 0,
    PIN1 ,
    PIN2 ,
    PIN3 ,
    PIN4 ,
    PIN5 ,
    PIN6 ,
    PIN7
}pin_index_t;

/**
 * @enum port_index_t
 * @brief GPIO port index.
 */
typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}port_index_t;

/**
 * @struct pin_config_t
 * @brief GPIO pin configuration structure.
 *
 * This structure holds all configuration parameters
 * required to initialize a GPIO pin.
 */
typedef struct {
    uint8 port            :  3  ;  /* @ref port_index_t */ /**< GPIO port index */
    uint8 pin             :  3  ;  /* @ref pin_index_t */ /**< GPIO pin number */
    uint8 direction       :  1  ;  /* @ref direction_t */ /**< GPIO direction */
    uint8 logic           :  1  ;  /* @ref Logic_t */ /**< Initial logic level */
}pin_config_t;


/* Section : Function Declarations */

#if CONFIG_ENABLE == GPIO_PORT_PIN_CONFIGURATION

/**
 * @brief Initialize the direction of a GPIO pin.
 *
 * @param[in] _pin_config_ Pointer to pin configuration structure.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_pin_direction_initialize (const pin_config_t *_pin_config_);

/**
 * @brief Get the direction status of a GPIO pin.
 *
 * @param[in]  _pin_config_ Pointer to pin configuration structure.
 * @param[out] dir_status Pointer to store direction status.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config_ , direction_t *dir_status);

/**
 * @brief Write a logic value to a GPIO pin.
 *
 * @param[in] _pin_config_ Pointer to pin configuration structure.
 * @param[in] logic Logic level to write.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_pin_write_logic ( pin_config_t *_pin_config_ , Logic_t logic );

/**
 * @brief Read the logic level of a GPIO pin.
 *
 * @param[in]  _pin_config_ Pointer to pin configuration structure.
 * @param[out] logic Pointer to store logic level.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config_ , Logic_t *logic );

/**
 * @brief Toggle the logic level of a GPIO pin.
 *
 * @param[in] _pin_config_ Pointer to pin configuration structure.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_pin_toggle_logic ( pin_config_t *_pin_config_ );

/**
 * @brief Initialize a GPIO pin.
 *
 * @param[in] _pin_config_ Pointer to pin configuration structure.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_pin_initialize (const pin_config_t *_pin_config_);

#endif 

#if CONFIG_ENABLE == GPIO_PORT_CONFIGURATION

/**
 * @brief Initialize the direction of a GPIO port.
 *
 * @param[in] port GPIO port index.
 * @param[in] port_dir Port direction mask.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_port_direction_initialize (port_index_t port , uint8 port_dir);

/**
 * @brief Get the direction status of a GPIO port.
 *
 * @param[in]  port GPIO port index.
 * @param[out] direction_status Pointer to store port direction.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_port_get_direction_status (port_index_t port , uint8 *direction_status );

/**
 * @brief Write a logic value to a GPIO port.
 *
 * @param[in] port GPIO port index.
 * @param[in] logic Port logic value.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_port_write_logic (port_index_t port , uint8 logic);

/**
 * @brief Read the logic value of a GPIO port.
 *
 * @param[in]  port GPIO port index.
 * @param[out] logic Pointer to store port logic.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_port_read_logic (port_index_t port , uint8 *logic);

/**
 * @brief Toggle the logic value of a GPIO port.
 *
 * @param[in] port GPIO port index.
 *
 * @return Std_ReturnType operation status.
 */
Std_ReturnType gpio_port_toggle_logic (port_index_t port );

#endif

#endif	/* HAL_GPIO_H */

