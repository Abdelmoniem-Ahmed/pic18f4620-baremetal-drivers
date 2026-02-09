/* 
 * @file    ecu_led.c
 * @brief   LED ECUAL driver implementation
 *
 * @details
 * Provides implementation for initializing and controlling single LEDs.
 * Uses GPIO HAL functions to abstract register-level operations.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */

#include "ecu_led.h"

/**
 * @brief Initialize the LED pin as output with initial logic
 */

Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = 
      { .port = led->port_name,
        .pin  = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT ,
        .logic = led->led_status };
      ret = gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief Turn on the LED (logic HIGH)
 */

Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = led->port_name,
            .pin  = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT ,
            .logic = led->led_status };
        gpio_pin_write_logic(&pin_obj , GPIO_PIN_HIGH );
    }
    return ret;
}

/**
 * @brief Turn off the LED (logic LOW)
 */

Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = led->port_name,
            .pin  = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT ,
            .logic = led->led_status };
        gpio_pin_write_logic(&pin_obj , GPIO_PIN_LOW );
    }
    return ret;
}


/**
 * @brief Toggle the LED state
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = led->port_name,
            .pin  = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT ,
            .logic = led->led_status };
        gpio_pin_toggle_logic( &pin_obj );
    }
    return ret;
}

