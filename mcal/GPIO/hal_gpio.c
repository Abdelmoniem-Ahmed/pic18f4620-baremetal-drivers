/** 
 * @file hal_gpio.c
 * @brief GPIO HAL driver source file. 
 *
 * This file contains the implementation of GPIO pin-level
 * and port-level APIs for the PIC18F4620 microcontroller.
 *
 * @author Abdelmoniem Ahmed
 * @linkedin <- https://www.linkedin.com/in/abdelmoniem-ahmed/ ->
 */
#include "hal_gpio.h"

/* Arrays mapping port index to corresponding TRIS, LAT and PORT registers */
/**
 * @brief Lookup table for TRIS, LAT and PORT registers.
 *
 * Index corresponds to port_index_t.
 */
static volatile uint8 * const tris_registers[] = {&TRISA , &TRISB , &TRISC , &TRISD ,&TRISE  };
static volatile uint8 * const lat_registers[]  = {&LATA  , &LATB  , &LATC  , &LATD  , &LATE  };
static volatile uint8 * const port_registers[] = {&PORTA , &PORTB , &PORTC , &PORTD , &PORTE };


#if CONFIG_ENABLE == GPIO_PORT_PIN_CONFIGURATION

Std_ReturnType gpio_pin_direction_initialize (const pin_config_t *_pin_config_){
    Std_ReturnType ret = E_NOT_OK ;
    if( (NULL == _pin_config_) || ((PORT_PIN_MAX_NUMBER-1) < _pin_config_->pin)){
        ret = E_NOT_OK ;
    }
    else{
        ret = E_OK ;
        switch(_pin_config_->direction){
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*tris_registers[_pin_config_->port] , _pin_config_->pin );
            break ;  
            case GPIO_DIRECTION_INPUT :
                SET_BIT(*tris_registers[_pin_config_->port] , _pin_config_->pin);
            break ;
            default : ret = E_NOT_OK ;
        }
        
    }
    return ret ;
}

Std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config_ , direction_t *dir_status){
    Std_ReturnType ret = E_OK ;
    if((NULL == _pin_config_) || (NULL == dir_status) || ( (PORT_PIN_MAX_NUMBER - 1) < _pin_config_->pin ) ){
        ret = E_NOT_OK ;
    }
    else{
        *dir_status = READ_BIT(*tris_registers[_pin_config_->port] , _pin_config_->pin);
    }
    return ret;
}

Std_ReturnType gpio_pin_write_logic ( pin_config_t *_pin_config_ , Logic_t logic ){
    Std_ReturnType ret = E_OK;
    if( (NULL == _pin_config_) || ((PORT_PIN_MAX_NUMBER-1) < _pin_config_->pin) ){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_PIN_LOW  :
                CLEAR_BIT(*lat_registers[_pin_config_->port] , _pin_config_->pin);
                break;
            case GPIO_PIN_HIGH :
                SET_BIT(*lat_registers[_pin_config_->port] , _pin_config_->pin);
                break;
            default : ret = E_NOT_OK ;   
        }
    }
    return ret;
}

Std_ReturnType gpio_pin_initialize (const pin_config_t *_pin_config_){
    Std_ReturnType ret = E_NOT_OK ;
    if( (NULL == _pin_config_) || ((PORT_PIN_MAX_NUMBER-1) < _pin_config_->pin)){
        ret = E_NOT_OK ;
    }
    else{
        ret = E_OK ;
        ret = gpio_pin_direction_initialize(_pin_config_);
        ret = gpio_pin_write_logic(_pin_config_ , _pin_config_->logic);
        }
    return ret ;
}


Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config_ , Logic_t *logic ){
    Std_ReturnType ret = E_OK ;
    if((NULL == _pin_config_) || (NULL == logic) || ( (PORT_PIN_MAX_NUMBER - 1) < _pin_config_->pin ) ){
        ret = E_NOT_OK ;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config_->port] , _pin_config_->pin);
    }
    return ret;
}

Std_ReturnType gpio_pin_toggle_logic ( pin_config_t *_pin_config_ ){
    Std_ReturnType ret = E_OK;
    if( (NULL == _pin_config_) || ((PORT_PIN_MAX_NUMBER-1) < _pin_config_->pin) ){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_registers[_pin_config_->port] , _pin_config_->pin);
    }
    return ret;
}

#endif


#if CONFIG_ENABLE == GPIO_PORT_CONFIGURATION

Std_ReturnType gpio_port_direction_initialize (port_index_t port , uint8 port_dir){
    Std_ReturnType ret = E_OK ;
    if((port > ( PORT_MAX_NUMBER - 1 ))){
        ret = E_NOT_OK ;
    }
    else{
       *tris_registers[port] = port_dir;
    }
    return ret;
}

Std_ReturnType gpio_port_get_direction_status (port_index_t port , uint8 *direction_status ){
    Std_ReturnType ret = E_OK ;
    if(port > ( PORT_MAX_NUMBER - 1 ) || (NULL == direction_status)){
        ret = E_NOT_OK ;
    }
    else{
        *direction_status = *tris_registers[port];
    }
    return ret;
}

Std_ReturnType gpio_port_write_logic (port_index_t port , uint8 logic){
    Std_ReturnType ret = E_OK ;
    if(port > ( PORT_MAX_NUMBER - 1 )){
        ret = E_NOT_OK ;
    }
    else{
        *lat_registers[port] = logic ;
    }
    return ret;
}

Std_ReturnType gpio_port_read_logic (port_index_t port , uint8 *logic){
    Std_ReturnType ret = E_OK ;
    if(port > ( PORT_MAX_NUMBER - 1 ) || (NULL == logic)){
        ret = E_NOT_OK ;
    }
    else{
        *logic = *lat_registers[port] ;
    }
    return ret;
}

Std_ReturnType gpio_port_toggle_logic (port_index_t port ){
    Std_ReturnType ret = E_OK ;
    if(port > ( PORT_MAX_NUMBER - 1 )){
        ret = E_NOT_OK ;
    }
    else{
        *lat_registers[port] ^= PORT_MASK ;
    }
    return ret;
}

#endif
