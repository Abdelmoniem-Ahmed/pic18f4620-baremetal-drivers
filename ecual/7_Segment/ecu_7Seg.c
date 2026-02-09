/* 
 * @file    ecu_7Seg.c
 * @brief   7-Segment ECUAL driver implementation
 *
 * @details
 * This file contains implementation for controlling a 4-bit 7-segment display
 * using GPIO HAL driver services.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 *
 * @author  Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @date    2026
 */

#include"ecu_7Seg.h"

/**
 * @brief Initialize 7-segment GPIO pins as outputs
 */
Std_ReturnType seven_segment_initialize( segment_t * seg){
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
       ret = E_NOT_OK; 
    }
    else{
        
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
        
    }
    return ret;
}

/**
 * @brief Write a number (0-9) to the 7-segment display
 */
Std_ReturnType seven_segment_write_number(const segment_t * seg , uint8 number ){
    Std_ReturnType ret = E_OK;
    if((NULL == seg) || ( 9 < number )){
       ret = E_NOT_OK; 
    }
    else{
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]) ,   number & 0x01 );
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]) , ((number >> 1) & 0x01) );
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]) , ((number >> 2) & 0x01) );
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]) , ((number >> 3) & 0x01) );
    }
    return ret;
}

