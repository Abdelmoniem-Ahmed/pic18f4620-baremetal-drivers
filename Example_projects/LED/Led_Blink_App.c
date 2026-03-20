#include"Led_Blink_app.h"

/* static Variable Definition */
static led_t led[8] = {
    {.port_name = PORTC_INDEX,.pin = PIN0,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN1,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN2,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN3,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN4,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN5,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN6,.led_status = GPIO_PIN_LOW},
    {.port_name = PORTC_INDEX,.pin = PIN7,.led_status = GPIO_PIN_LOW}
};

/* Function Definition */

/* This Function Use Led driver which could be not efficient as 
 * write to port using hal gpio driver 
 */

void Led_Blink_app(void){
    
    for(uint8 i = 0 ; i<8 ; i++){
        led_initialize(&(led[i]));
    }
    
    while(1){
        
        for(uint8 i = 0; i < 8 ; i += 2){
            led_turn_toggle(&(led[i]));
        }
        __delay_ms(250);
        
        for(uint8 i = 0; i < 10 ; i++){
            for(uint8 i = 0; i < 8 ; i++){
                led_turn_toggle(&(led[i]));
            }
            __delay_ms(250); 
        }  
        
        for(uint8 i = 0 ; i<8 ; i++){
            led_turn_off(&led[i]);
        }
        
        for(uint8 i = 0; i < 10 ; i++){
            for(uint8 j = 0 ; j<8 ; j++){
                led_turn_on(&(led[j]));
                __delay_ms(50);
                led_turn_off(&(led[j]));
            }
        }
    }
}


/* This Is More Efficient */

void Led_Blink_Hal_app(void){
    
    for(uint8 i = 0 ; i<8 ; i++){
        led_initialize(&(led[i]));
    }
    
    while(1){
        for(uint8 i = 0; i < 10 ; i++){
            gpio_port_write_logic(PORTC_INDEX , 0x55);
            __delay_ms(250);
            gpio_port_write_logic(PORTC_INDEX , 0xAA);
            __delay_ms(250);    
        }
        gpio_port_write_logic(PORTC_INDEX , 0x00);
        
        for(uint8 i = 0; i < 10 ; i++){
            gpio_port_write_logic(PORTC_INDEX , 0x0F);
            __delay_ms(250);
            gpio_port_write_logic(PORTC_INDEX , 0xF0);
            __delay_ms(250);    
        }
        gpio_port_write_logic(PORTC_INDEX , 0x00);
        
        for(uint8 i = 0; i < 10 ; i++){
            for(uint8 j = 0; j < 8 ; j++ ){
                gpio_port_write_logic(PORTC_INDEX , (uint8 )(0x01 << j));
                __delay_ms(50); 
            } 
        }
        gpio_port_write_logic(PORTC_INDEX , 0x00);
    }
    
}
