#include"Matrix_Keypad_app.h"


static void TMR_Handler(void);

static timer1_t tmr_10ms = {
    .timer1_preload_value = 45536,
    .prescaler_division = timer1_prescaler_dive_1,
    .timer1_mode = TIMER1_TIMER_MODE_CFG,
    .timer1_osc_cfg = TIMER1_OSC_DISABLE,
    .timer1_reg_rw_mode = TIMER1_RD_16BIT_MODE_CFG,
    .TMR_InterruptHandler = TMR_Handler,
};

static keypad_t matrix_keypad = {
    .keypad_row_pins[0].port = PORTC_INDEX , .keypad_row_pins[0].pin = PIN0 ,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[0].logic = GPIO_PIN_LOW,
    
    .keypad_row_pins[1].port = PORTC_INDEX , .keypad_row_pins[1].pin = PIN1 ,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[1].logic = GPIO_PIN_LOW,
    
    .keypad_row_pins[2].port = PORTC_INDEX , .keypad_row_pins[2].pin = PIN2 ,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[2].logic = GPIO_PIN_LOW,
    
    .keypad_row_pins[3].port = PORTC_INDEX , .keypad_row_pins[3].pin = PIN3 ,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[3].logic = GPIO_PIN_LOW,
    
    .keypad_column_pins[0].port = PORTC_INDEX , .keypad_column_pins[0].pin = PIN4 ,
    .keypad_column_pins[0].direction = GPIO_DIRECTION_INPUT ,
    
    .keypad_column_pins[1].port = PORTC_INDEX , .keypad_column_pins[1].pin = PIN5 ,
    .keypad_column_pins[1].direction = GPIO_DIRECTION_INPUT ,

    .keypad_column_pins[2].port = PORTC_INDEX , .keypad_column_pins[2].pin = PIN6 ,
    .keypad_column_pins[2].direction = GPIO_DIRECTION_INPUT ,

    .keypad_column_pins[3].port = PORTC_INDEX , .keypad_column_pins[3].pin = PIN7 ,
    .keypad_column_pins[3].direction = GPIO_DIRECTION_INPUT ,
};
static chr_lcd_4bit_t Chr_Lcd_4Bit = {
    .lcd_data[0].port = PORTB_INDEX ,
    .lcd_data[0].pin  = PIN4 ,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_data[1].port = PORTB_INDEX ,
    .lcd_data[1].pin  = PIN5 ,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_data[2].port = PORTB_INDEX ,
    .lcd_data[2].pin  = PIN6 ,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_data[3].port = PORTB_INDEX ,
    .lcd_data[3].pin  = PIN7 ,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_en.port = PORTD_INDEX ,
    .lcd_en.pin  = PIN4 ,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_rs.port = PORTD_INDEX ,
    .lcd_rs.pin  = PIN5 ,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT ,
};

//static led_t led0 = {
//    .port_name  = PORTD_INDEX , .pin = PIN0 , .led_status = GPIO_PIN_LOW
//};
//
//static led_t led1 = {
//    .port_name  = PORTD_INDEX , .pin = PIN1 , .led_status = GPIO_PIN_LOW
//};

static uint8 keypad_val_crnt = NO_KEY;
static uint8 keypad_val_prev = NO_KEY;


static volatile uint8 tmr_10ms_flag = ZERO_INIT;

void Matrix_Keypad_Led_App(void){
    keypad_initialize(&matrix_keypad);
    lcd_4bit_initialize(&Chr_Lcd_4Bit);
    timer1_init(&tmr_10ms);
//    led_initialize(&led0);
//    led_initialize(&led1);
    
    lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
    lcd_4bit_send_command(&Chr_Lcd_4Bit , _LCD_CURSOR_OFF_DISPLAY_ON);
    
    while(1){
        
        if(tmr_10ms_flag){
            tmr_10ms_flag = 0;
            Keypad_Update(&matrix_keypad ,&keypad_val_crnt );
        }

        if((NO_KEY == keypad_val_prev) && (NO_KEY != keypad_val_crnt) ){
            lcd_4bit_send_char_data(&Chr_Lcd_4Bit ,keypad_val_crnt );
        }
        keypad_val_prev = keypad_val_crnt;  
    } 
}

static void TMR_Handler(void){
    tmr_10ms_flag = 1;
}
