/**
 * @file ecu_Chr_lcd.c
 * @brief Character LCD ECUAL driver implementation
 *
 * @details
 * This file contains the implementation of an HD44780-compatible
 * character LCD driver.
 *
 * The driver:
 * - Is implemented in the ECUAL layer
 * - Uses GPIO MCAL services only
 * - Does not access hardware registers directly
 * - Supports compile-time selection of 4-bit or 8-bit mode
 *
 * Design characteristics:
 * - Blocking implementation
 * - Polling-based (no interrupts)
 * - LCD busy flag is NOT read
 * - Timing requirements are satisfied using software delays
 *
 * Configuration:
 * - Interface mode is selected via ecu_Chr_lcd_cfg.h
 * - Only one mode is compiled at a time
 *
 * @note
 * This module assumes that:
 * - System clock is already configured
 * - GPIO driver is initialized correctly
 *
 * Layer: ECUAL
 * Target MCU: PIC18F4620
 *
 * @author Abdelmoniem Ahmed
 * @linkedin https://www.linkedin.com/in/abdelmoniem-ahmed/
 * @date 2026
 */

#include"ecu_Chr_lcd.h"

#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_4BIT_MODE_ENABLE

/**
 * @brief Send lower or upper 4 bits to LCD data lines
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t * lcd , uint8 _data_command);

/**
 * @brief Generate enable pulse for 4-bit LCD mode
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t * lcd);

/**
 * @brief Set cursor position in 4-bit mode
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column);

#endif

#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_8BIT_MODE_ENABLE

/**
 * @brief Generate enable pulse for 8-bit LCD mode
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t * lcd);

/**
 * @brief Set cursor position in 8-bit mode
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column);

#endif

Std_ReturnType convert_byte_to_string(uint8 data , uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == str) {
        ret = E_NOT_OK;
    }
    else{
        memset(str , "\0" , 4);
        sprintf(str , "%i" , data);
    }
    return ret ;
}

Std_ReturnType convert_short_to_string(uint16 data , uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 temp_string[6] = {0} , l_counter = 0;
    if (NULL == str) {
        ret = E_NOT_OK;
    }
    else{
        memset(temp_string , '\0' , 6);
        memset(str , ' ' , 6);
        sprintf(temp_string , "%i" , data);
        while( '\0' != temp_string[l_counter]){
            str[l_counter] = temp_string[l_counter];
            l_counter++;
        }
        str[5] = '\0';
    }
    return ret ;
}

Std_ReturnType convert_int_to_string(uint32 data , uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == str) {
        ret = E_NOT_OK;
    }
    else{
        memset(str , '\0' , 11);
        sprintf(str , "%i" , data);
    }
    return ret ;
}


#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_4BIT_MODE_ENABLE

Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t * lcd ){
    Std_ReturnType ret = E_OK ;
    uint8 lcd_pin_counter = 0 ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(lcd_pin_counter = 0 ; lcd_pin_counter < 4 ; lcd_pin_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[lcd_pin_counter]));            
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2LINE );
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2LINE );
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2LINE );
        
        ret = lcd_4bit_send_command(lcd , _LCD_CLEAR );
        ret = lcd_4bit_send_command(lcd , _LCD_RETURN_HOME );
        ret = lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE );
        ret = lcd_4bit_send_command(lcd , _LCD_CURSOR_OFF_DISPLAY_ON );
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd , _LCD_DDRAM_START );
    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t * lcd , uint8 command ){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_PIN_LOW);
        ret = lcd_send_4bits(lcd , (command >> 4 ));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd , (command));
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t * lcd , uint8 data){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_PIN_HIGH);
        ret = lcd_send_4bits(lcd , (data >> 4 ));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd , (data));
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column ,  uint8 data){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        lcd_4bit_set_cursor(lcd , row , column);
        lcd_4bit_send_char_data(lcd , data);
    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t * lcd , uint8 *str ){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        while (*str) {
            ret = lcd_4bit_send_char_data( lcd , *str++ );
            }

    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column, uint8 *str ){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd , row , column);
        ret = lcd_4bit_send_string(lcd , str);
    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t * lcd , uint8 row 
                                      , uint8 column , const uint8 _chr[] , uint8 mem_position )
{
    Std_ReturnType ret = E_OK ;
    uint8 lcd_custom_counter = ZERO_INIT;
    mem_position--;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd , (_LCD_CGRAM_START + 8 * mem_position) );
        for (lcd_custom_counter = 0; lcd_custom_counter < 8; lcd_custom_counter++) 
        {
            ret = lcd_4bit_send_char_data(lcd , _chr[lcd_custom_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd , row , column , mem_position);
    }
    return ret ;
}


#elif CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_8BIT_MODE_ENABLE

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t * lcd ){
    Std_ReturnType ret = E_OK ;
    uint8 lcd_pin_counter = 0 ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(lcd_pin_counter = 0 ; lcd_pin_counter < 8 ; lcd_pin_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[lcd_pin_counter]));            
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2LINE );
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2LINE );
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2LINE );
        
        ret = lcd_8bit_send_command(lcd , _LCD_CLEAR );
        ret = lcd_8bit_send_command(lcd , _LCD_RETURN_HOME );
        ret = lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE );
        ret = lcd_8bit_send_command(lcd , _LCD_CURSOR_OFF_DISPLAY_ON );
        ret = lcd_8bit_send_command(lcd , _LCD_DDRAM_START );
        
    }
    return ret ;
}


Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t * lcd , uint8 command ){
    Std_ReturnType ret = E_OK ;
    uint8 l_lcd_data_counter = ZERO_INIT ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_PIN_LOW);
        for(l_lcd_data_counter = 0 ; l_lcd_data_counter < 8 ; l_lcd_data_counter++ ){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_data_counter]) 
                                    , (command >> l_lcd_data_counter) & BIT_MASK);
        }
        ret = lcd_8bit_send_enable_signal(lcd); 
    }
    return ret ;
}


Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t * lcd , uint8 data){
    Std_ReturnType ret = E_OK ;
    uint8 l_lcd_data_counter = ZERO_INIT ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_PIN_HIGH);
        for(l_lcd_data_counter = 0 ; l_lcd_data_counter < 8 ; l_lcd_data_counter++ ){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_data_counter]) 
                                    , (data >> l_lcd_data_counter) & BIT_MASK);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret ;

}


Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column ,  uint8 data){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd , row , column);
        ret = lcd_8bit_send_char_data(lcd , data);
    }
        return ret ;
}


Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t * lcd , uint8 *str ){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        while (*str) {
            ret = lcd_8bit_send_char_data(lcd , *str++ );  
        }
    }
        return ret ;
}


Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column, uint8 *str ){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        lcd_8bit_set_cursor(lcd  , row , column );
        lcd_8bit_send_string(lcd , str);
    }    
    
    return ret ;

}


Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t * lcd , uint8 row 
                                       , uint8 column , const uint8 _chr[] , uint8 mem_position )
{
    Std_ReturnType ret = E_OK ;
    uint8 lcd_custom_counter = ZERO_INIT;
    mem_position--;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_send_command(lcd , (_LCD_CGRAM_START + 8 * mem_position) );
        for (lcd_custom_counter = 0; lcd_custom_counter < 8; lcd_custom_counter++) 
        {
            ret = lcd_8bit_send_char_data(lcd , _chr[lcd_custom_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd , row , column , mem_position);
    }
    return ret ;
}

#endif

#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_4BIT_MODE_ENABLE

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t * lcd , uint8 _data_command){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , ((_data_command >> 0 ) & (uint8)0x01) );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , ((_data_command >> 1 ) & (uint8)0x01) );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , ((_data_command >> 2 ) & (uint8)0x01) );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , ((_data_command >> 3 ) & (uint8)0x01) );
    return ret ;
}


static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch (row) {
        case ROW1 : ret = lcd_4bit_send_command(lcd , (0x80 + column)); break;
        case ROW2 : ret = lcd_4bit_send_command(lcd , (0xC0 + column)); break;
        case ROW3 : ret = lcd_4bit_send_command(lcd , (0x94 + column)); break;
        case ROW4 : ret = lcd_4bit_send_command(lcd , (0xd4 + column)); break;
        default   :  ;
    }
    return ret ;
}


static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t * lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_PIN_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_PIN_LOW);
    return ret ;
}

#endif

#if CHR_LCD_4BIT_OR_8BIT_MODE_CFG == CHR_LCD_8BIT_MODE_ENABLE

static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t * lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_PIN_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_PIN_LOW);
    return ret ;
}


static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch (row) {
        case ROW1 : ret = lcd_8bit_send_command(lcd , (0x80 + column)); break;
        case ROW2 : ret = lcd_8bit_send_command(lcd , (0xC0 + column)); break;
        case ROW3 : ret = lcd_8bit_send_command(lcd , (0x94 + column)); break;
        case ROW4 : ret = lcd_8bit_send_command(lcd , (0xd4 + column)); break;
        default   :  ;
    }
    return ret ;
}

#endif



