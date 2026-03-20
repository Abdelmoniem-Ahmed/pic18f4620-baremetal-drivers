
#include "Chr_LCD_app.h"


static chr_lcd_4bit_t Chr_Lcd_4Bit = {
    .lcd_data[0].port = PORTD_INDEX ,
    .lcd_data[0].pin  = PIN0 ,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_data[1].port = PORTD_INDEX ,
    .lcd_data[1].pin  = PIN1 ,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_data[2].port = PORTD_INDEX ,
    .lcd_data[2].pin  = PIN2 ,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_data[3].port = PORTD_INDEX ,
    .lcd_data[3].pin  = PIN3 ,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_en.port = PORTC_INDEX ,
    .lcd_en.pin  = PIN7 ,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_rs.port = PORTC_INDEX ,
    .lcd_rs.pin  = PIN6 ,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT ,
};

static uint8 custom_full_battery[] = {
    0x0E,
    0x0E,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x00
};
static uint8 custom_eighty_percent_battery[] = {
    0x0E,
    0x0A,
    0x11,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x00
};
static uint8 custom_fifty_percent_battery[] = {
    0x0E,
    0x0A,
    0x11,
    0x11,
    0x1F,
    0x1F,
    0x1F,
    0x00
};
static uint8 custom_twenty_percent_battery[] = {
    0x0E,
    0x0A,
    0x11,
    0x11,
    0x11,
    0x1F,
    0x1F,
    0x00
};
static uint8 custom_empty_battery[] = {
    0x0E,
    0x0A,
    0x11,
    0x11,
    0x11,
    0x11,
    0x1F,
    0x00
};
static uint8 custom_bluetooth[] = {
  0x04,
  0x06,
  0x15,
  0x0E,
  0x0E,
  0x15,
  0x06,
  0x04
};
static uint8 custom_wifi[] = {
  0x0E,
  0x1B,
  0x00,
  0x0E,
  0x0A,
  0x00,
  0x04,
  0x00
};

void Chr_LCD_app(void){
    lcd_4bit_initialize(&Chr_Lcd_4Bit);
    
    while(1){
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
        lcd_4bit_send_command(&Chr_Lcd_4Bit , _LCD_CURSOR_OFF_DISPLAY_ON);

        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 3 , "AbdElmoniem Ahmed");
        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW3 , 3 , "Embedded Engineer");
        __delay_ms(1000);
        
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_full_battery , 1 );
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 19 , custom_wifi , 6 );
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 18 , custom_bluetooth , 7 );
        __delay_ms(1000);
        
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(500);
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(500);
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(500);
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(500);
        
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(500);
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(500);
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(500);
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(500);
                                                                                 
        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW3 , 3 , "                   ");
        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 3 , "Discharge          ");
        __delay_ms(1000);
        
        /* Discharge */
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_eighty_percent_battery , 2 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_fifty_percent_battery , 3 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_twenty_percent_battery , 4 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_empty_battery , 5 );
        __delay_ms(1000);
        
        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 3 , "Charging        ");
        __delay_ms(1000);
        
        /* Charging */
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_twenty_percent_battery , 4 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_fifty_percent_battery , 3 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_eighty_percent_battery , 2 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_full_battery , 1 );        
        __delay_ms(1000);
        
        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 3 , "Discharge          ");
        __delay_ms(1000);
        
        /* Discharge */
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_eighty_percent_battery , 2 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_fifty_percent_battery , 3 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_twenty_percent_battery , 4 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_empty_battery , 5 );
        __delay_ms(1000);
        
        lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 3 , "Charging           ");
        __delay_ms(1000);
        
        /* Charging */
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_twenty_percent_battery , 4 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_fifty_percent_battery , 3 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_eighty_percent_battery , 2 );
        __delay_ms(1000);
        lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW1 , 20 , custom_full_battery , 1 );        
        __delay_ms(1000);
    }    
}
