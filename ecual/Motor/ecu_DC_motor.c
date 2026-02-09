/* 
 * @file    ecu_DC_motor.c
 * @brief   DC Motor ECUAL driver implementation
 *
 * @details
 * Implements functions to initialize and control a DC motor.
 * Motor direction is controlled by two GPIO pins.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */


#include"ecu_DC_motor.h"

/*---------------- Functions ----------------*/

Std_ReturnType dc_motor_initialize(const dc_motor_t * motor){
    Std_ReturnType ret = E_OK;

    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_initialize(&(motor->dc_motor[DC_MOTOR_PIN1]));
        gpio_pin_initialize(&(motor->dc_motor[DC_MOTOR_PIN2]));
        
    }
    return ret;
}

Std_ReturnType dc_motor_move_forward(dc_motor_t * motor){
    
    Std_ReturnType ret = E_OK;

    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_write_logic(&(motor->dc_motor[DC_MOTOR_PIN1]) , GPIO_PIN_HIGH);
        gpio_pin_write_logic(&(motor->dc_motor[DC_MOTOR_PIN2]) , GPIO_PIN_LOW);
        
    }
    return ret;
}

Std_ReturnType dc_motor_move_backward(dc_motor_t * motor){
    Std_ReturnType ret = E_OK;

    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_write_logic(&(motor->dc_motor[DC_MOTOR_PIN1]) , GPIO_PIN_LOW);
        gpio_pin_write_logic(&(motor->dc_motor[DC_MOTOR_PIN2]) , GPIO_PIN_HIGH);
        
    }
    return ret;
}

Std_ReturnType dc_motor_stop(dc_motor_t * motor){
    Std_ReturnType ret = E_OK;

    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
            
        gpio_pin_write_logic(&(motor->dc_motor[DC_MOTOR_PIN1]) , GPIO_PIN_LOW);
        gpio_pin_write_logic(&(motor->dc_motor[DC_MOTOR_PIN2]) , GPIO_PIN_LOW);
        
    }
    return ret;
}

