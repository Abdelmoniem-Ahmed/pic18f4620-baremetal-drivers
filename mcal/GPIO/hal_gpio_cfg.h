/**
 * @file hal_gpio_cfg.h
 * @brief GPIO configuration header file.
 *
 * This file contains compile-time configuration macros
 * used to enable or disable GPIO driver features.
 *
 * The configuration options allow reducing code size
 * by excluding unused functionalities.
 *
 * @author Abdelmoniem Ahmed
 * @linkedin <- https://www.linkedin.com/in/abdelmoniem-ahmed/ ->
 * @date 2026
 */


#ifndef HAL_GPIO_CFG_H
#define	HAL_GPIO_CFG_H

/**
 * @brief Enable a GPIO feature at compile time.
 */
#define CONFIG_ENABLE  0X01

/**
 * @brief Disable a GPIO feature at compile time.
 */
#define CONFIG_DISABLE 0X00

/* Enable pin-level GPIO APIs */
#define GPIO_PORT_PIN_CONFIGURATION        CONFIG_ENABLE

/* Enable port-level GPIO APIs */
#define GPIO_PORT_CONFIGURATION            CONFIG_ENABLE

#endif	/* HAL_GPIO_CFG_H */

