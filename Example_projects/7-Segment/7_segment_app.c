#include "7_segment_app.h"


static uint8 counter = 0;

static segment_t seg_com_Cathode  = {
    .segment_pins[SEGMENT_PIN0].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN0].pin  = PIN0,
    .segment_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[SEGMENT_PIN1].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN1].pin  = PIN1,
    .segment_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[SEGMENT_PIN2].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN2].pin  = PIN2,
    .segment_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[SEGMENT_PIN3].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN3].pin  = PIN3,
    .segment_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_type = SEGMENT_COMMON_CATHODE
};

static segment_t seg_com_Anode  = {
    .segment_pins[SEGMENT_PIN0].port = PORTD_INDEX,
    .segment_pins[SEGMENT_PIN0].pin  = PIN0,
    .segment_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[SEGMENT_PIN1].port = PORTD_INDEX,
    .segment_pins[SEGMENT_PIN1].pin  = PIN1,
    .segment_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[SEGMENT_PIN2].port = PORTD_INDEX,
    .segment_pins[SEGMENT_PIN2].pin  = PIN2,
    .segment_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[SEGMENT_PIN3].port = PORTD_INDEX,
    .segment_pins[SEGMENT_PIN3].pin  = PIN3,
    .segment_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_type = SEGMENT_COMMON_ANODE
};

void Seven_Segment_app(void){
    
    seven_segment_initialize(&seg_com_Cathode);
    seven_segment_initialize(&seg_com_Anode);
    
    while(1){
        if( MAX_DIGIT < counter){
            counter = 0;
        }
        seven_segment_write_number(&seg_com_Cathode ,counter );
        seven_segment_write_number(&seg_com_Anode , MAX_DIGIT - counter );
        counter++;
        __delay_ms(500);
        
    }
    
    
}