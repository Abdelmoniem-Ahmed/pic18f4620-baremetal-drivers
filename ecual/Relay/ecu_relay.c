/* 
 * @file    ecu_relay.c
 * @brief   Relay ECUAL driver implementation
 *
 * @details
 * Implements functions to initialize and control a relay via GPIO.
 * Supports ON, OFF, and toggle operations.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */

/* Section : Includes */

#include"ecu_relay.h"

/* Section : Macro Declaration */

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

/* Section : Function Declarations */

Std_ReturnType relay_initialize(const relay_t * relay_data ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay_data){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = relay_data->relay_port,
            .pin  = relay_data->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay_data->relay_status
        };
      ret = gpio_pin_initialize(&pin_obj);
      
    }
    return ret;
}


Std_ReturnType relay_turn_on(relay_t * relay_data ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay_data){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = relay_data->relay_port,
            .pin  = relay_data->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT ,
            .logic = relay_data->relay_status };
        gpio_pin_write_logic(&pin_obj , GPIO_PIN_HIGH );
    }
    return ret;
}

Std_ReturnType relay_turn_off(relay_t * relay_data ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay_data){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = relay_data->relay_port,
            .pin  = relay_data->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT ,
            .logic = relay_data->relay_status };
        gpio_pin_write_logic(&pin_obj , GPIO_PIN_LOW );
    }
    return ret;
}

Std_ReturnType relay_turn_toggle(relay_t * relay_data ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay_data){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = 
        {   .port = relay_data->relay_port,
            .pin  = relay_data->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT ,
            .logic = relay_data->relay_status };
        gpio_pin_toggle_logic(&pin_obj );
    }
    return ret;
}

