#include "Smart_Home_app.h"

/********************** Function Declaration **********************/

static void Smart_Home_app_init(void);
static void RealTimeClock_DS1307_Date(void);
static void TemperatureSensor_TC74(void);
static void Chr_LCD_Hello_MSG(void);
static void Chr_LCD_Date_Time_Temp_MSG(void);
static void Slave_Communication(void);
static void TMR0_Handler(void);

/********************** Variable Definition **********************/

static usart_t uart_obj = {
    .baudrate = 9600,
    .baudrate_cfg = BAUDRATE_ASYNC_8BIT_LOW_SPEED,
    
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE,
    
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_DISABLE,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE,
};
static mssp_i2c_t i2c_obj = {
    .i2c_clock  = 100000,
    .i2c_cfg.i2c_mode = MSSP_I2C_MASTER_MODE,
    .i2c_cfg.i2c_mode_cfg = MSSP_I2C_MASTER_MODE_DEFINED_CLK,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE_100kHZ,
    .i2c_cfg.i2c_SMBus_Control = I2C_SMBUS_DISABLE,
    
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
    
    .lcd_en.port = PORTA_INDEX ,
    .lcd_en.pin  = PIN2 ,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT ,
    
    .lcd_rs.port = PORTA_INDEX ,
    .lcd_rs.pin  = PIN3 ,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT ,
};
static timer0_t tim_10ms ={
    .timer0_preload_value = 45536,
    .prescaler_enable = PRESCALER_NOT_ASSIGNED_CFG,
    .counter_edge_select = TIMER0_RISING_EDGE_CFG,
    .clock_source = TIMER0_INTERNAL_CLK_SRC_CFG,
    .timer_resolution = TIMER0_16BIT_MODE_CFG,
    
    .TMR_InterruptHandler = TMR0_Handler,
};
static keypad_t matrix_keypad = {
    .keypad_row_pins[0].port = PORTD_INDEX , .keypad_row_pins[0].pin = PIN0 ,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[0].logic = GPIO_PIN_LOW,
    
    .keypad_row_pins[1].port = PORTD_INDEX , .keypad_row_pins[1].pin = PIN1 ,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[1].logic = GPIO_PIN_LOW,
    
    .keypad_row_pins[2].port = PORTD_INDEX , .keypad_row_pins[2].pin = PIN2 ,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[2].logic = GPIO_PIN_LOW,
    
    .keypad_row_pins[3].port = PORTD_INDEX , .keypad_row_pins[3].pin = PIN3 ,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT ,
    .keypad_row_pins[3].logic = GPIO_PIN_LOW,
    
    .keypad_column_pins[0].port = PORTD_INDEX , .keypad_column_pins[0].pin = PIN4 ,
    .keypad_column_pins[0].direction = GPIO_DIRECTION_INPUT ,
    
    .keypad_column_pins[1].port = PORTD_INDEX , .keypad_column_pins[1].pin = PIN5 ,
    .keypad_column_pins[1].direction = GPIO_DIRECTION_INPUT ,

    .keypad_column_pins[2].port = PORTD_INDEX , .keypad_column_pins[2].pin = PIN6 ,
    .keypad_column_pins[2].direction = GPIO_DIRECTION_INPUT ,

    .keypad_column_pins[3].port = PORTD_INDEX , .keypad_column_pins[3].pin = PIN7 ,
    .keypad_column_pins[3].direction = GPIO_DIRECTION_INPUT ,
};

static RealTimeClock_DS1307_t time;

static Std_ReturnType ret = E_NOT_OK;

/* Lock App Variable */

static uint8 password_attempt = ZERO_INIT;
static uint8 password_counter = ZERO_INIT;

static uint8 password[] = "6102004" ;
static uint8 password_buffer[MAX_PASSWORD_DIGIT+1];
static uint8 pass_len = sizeof(password);

static uint8 keypad_val_crnt = NO_KEY;
static uint8 keypad_val_prev = NO_KEY;

static uint8 pass_status = PASSWORD_FAILED;

static uint8 match = 1;

static password_state_t password_state = PASSWORD_SHOW_PROMPT;

/* Application variable */

static uint8 space_msg[]    = "----------------------------------\r\n";

static uint8 Hello_msg_lcd[] = "Hello Embedded" ;
static uint8 Hello_msg2_lcd[] = "System World" ;
static uint8 system_start[] = "System Started" ;

static uint8 celsius[] = {
  0x06,
  0x09,
  0x06,
  0x00,
  0x07,
  0x04,
  0x07,
  0x00
};

static uint8 Date[12] ;
static uint8 Time[10] ;
static sint8 temp_msg[5];
static uint8 ack;

static volatile uint8  tmr0_10ms_flag = ZERO_INIT;
static volatile uint8 tmr0_1sec_counter = ZERO_INIT; 
static volatile uint16 tmr0_5sec_counter = ZERO_INIT;
static volatile uint16 tmr0_10sec_counter = ZERO_INIT;
static volatile uint8  app_locked_30sec = ZERO_INIT;


static volatile uint8 app_1sec_flag = 1;
static volatile uint8 app_5sec_flag = ZERO_INIT;
static volatile uint8 app_10sec_flag = ZERO_INIT;

static sint8 temp = ZERO_INIT;

static uint8 temp_log_addr_counter = 0;
static uint8 max_temp  = 0;
static uint8 min_temp  = 0xFF;
static uint8 last_temp = 0;

/********************** Function Definition **********************/

void Smart_Home_App(void){
    
    ret = keypad_initialize(&matrix_keypad);
    ret = timer0_init(&tim_10ms);
    ret = lcd_4bit_initialize(&Chr_Lcd_4Bit);    
    
    while((MAX_PASSWORD_ATTEMPT+1 > password_attempt) && (!pass_status) ){
        
        switch(password_state){
            
            case PASSWORD_SHOW_PROMPT :
                /* Clear LCD */
                lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
                lcd_4bit_send_command(&Chr_Lcd_4Bit , _LCD_CURSOR_OFF_DISPLAY_ON);
                /* Enter Password Message */
                lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 1 , "Enter Password : ");
                password_state = PASSWORD_READING;
                break;
                
            case PASSWORD_READING :
                if(tmr0_10ms_flag){
                    tmr0_10ms_flag = 0;
                    Keypad_Update(&matrix_keypad ,&keypad_val_crnt );
                }
                if((NO_KEY == keypad_val_prev) && (NO_KEY != keypad_val_crnt) ){
                    if(('=' != keypad_val_crnt) && ( (MAX_PASSWORD_DIGIT - 1) > password_counter) ){
                        password_buffer[password_counter] = keypad_val_crnt;
                        password_counter++;
                        lcd_4bit_send_char_data_pos(&Chr_Lcd_4Bit , ROW3 , password_counter , '*');
                    }
                    if(('=' == keypad_val_crnt) || ( (MAX_PASSWORD_DIGIT - 1) <= password_counter)){
                        password_state = PASSWORD_CHECK;
                        __delay_ms(500);
                    }
                }
                keypad_val_prev = keypad_val_crnt;
                break;
            
            case PASSWORD_CHECK :
                match = 1;
                password_buffer[password_counter] = '\0';
                password_counter++;
                if( password_counter == pass_len ){    
                    for(uint8 i = 0 ; i < password_counter ; i++ ){
                        if((password_buffer[i] != password[i] )){
                            match = 0;
                            break;
                        }
                    }
                }    
                else{
                    match = 0;
                }
                if(match){
                    password_state = PASSWORD_GRANTED;
                }
                else{
                    password_state = PASSWORD_DENIED;
                    password_counter = 0;
                    memset(password_buffer , 0 , sizeof(password_buffer) );
                }
                break;
                
            case PASSWORD_GRANTED :
                pass_status = PASSWORD_PASSED;
                lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
                lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 1 , "Access Granted! ");
                __delay_ms(2000);
                break;
            case PASSWORD_DENIED :
                password_attempt++;
                /* Clear LCD */
                lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
                lcd_4bit_send_command(&Chr_Lcd_4Bit , _LCD_CURSOR_OFF_DISPLAY_ON);
                /* Enter Password Message */
                lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 1 , "Invalid Password ");
                __delay_ms(1000);
                if( MAX_PASSWORD_ATTEMPT > password_attempt){
                    password_state = PASSWORD_SHOW_PROMPT;
                    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW3 , 5 , "try again ");
                    __delay_ms(2000);
                }
                else{
                    password_state = PASSWORD_LOCKED;
                }
                break;
            case PASSWORD_LOCKED :
                lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
                lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 1 , "System Locked ");
                lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW3 , 5 , "wait 30 seconds");
                app_locked_30sec = 0;
                /*  
                 * Wait ~30 seconds (3 × 10 sec ticks)
                 * Timer interrupt must continue running! 
                 */
                while(3 > app_locked_30sec);
                password_state = PASSWORD_SHOW_PROMPT;
                password_attempt = 0;
                pass_status = PASSWORD_FAILED;
                break;
            default :
                password_state = PASSWORD_SHOW_PROMPT;
                break;
        }
    }
         
    if(PASSWORD_PASSED == pass_status){
        Smart_Home_app_init();
        Chr_LCD_Hello_MSG();
        
        /* Clear LCD */
        lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
        lcd_4bit_send_command(&Chr_Lcd_4Bit , _LCD_CURSOR_OFF_DISPLAY_ON);
        
        while(1){

            if(1 == app_1sec_flag){
                app_1sec_flag = 0;
                ret = RealTimeClock_DS1307_Get_Date_Time(&time);
                RealTimeClock_DS1307_Date();    /* Construct The Date & Time Array */
                ret = TempSensor_TC74_Read_Temp(TEMP_SENSOR_ADDRESS , &temp);
                TemperatureSensor_TC74();       /* Construct The Temperature Array */

                /* After Array Construction , time to display */
                Chr_LCD_Date_Time_Temp_MSG();

                /* Send Temperature Value For Slave MCU */
                Slave_Communication();  
            }
            else{ /* Nothing */ }

            if(1 == app_5sec_flag){
                app_5sec_flag = 0;

                /* Change the arrays used for character lcd to be used for uart */
                Time[8] = '\r';
                Date[10] = '\r';
                temp_msg[3] = '\r';

                /* Debugging messages through uart */

                EUSART_ASYNC_Write_String_Blocking("Date : ", 7);
                EUSART_ASYNC_Write_String_Blocking(Date , sizeof(Date));
                EUSART_ASYNC_Write_String_Blocking("Time : ", 7);
                EUSART_ASYNC_Write_String_Blocking(Time , sizeof(Time));
                EUSART_ASYNC_Write_String_Blocking("Temperature : ", 14);
                EUSART_ASYNC_Write_String_Blocking(temp_msg , sizeof(temp_msg));
                EUSART_ASYNC_Write_String_Blocking(space_msg , sizeof(space_msg));
            }
            else{ /* Nothing */ }

            if(1 == app_10sec_flag){
                app_10sec_flag = 0;

                last_temp = temp;
                max_temp = max_temp > last_temp ? max_temp : last_temp ;
                min_temp = min_temp < last_temp ? min_temp : last_temp ;

                /* EEPROM Used For Data Logging,  EEPROM1_ADDRESS For Every Temp Value 
                 *                                EEPROM2_ADDRESS For max,min,last Temp Value
                 */
                EEPROM_24C02C_Write_Byte(EEPROM1_ADDRESS , temp_log_addr_counter++ , last_temp );
                EEPROM_24C02C_Write_Byte(EEPROM2_ADDRESS , MAX_TEMP_VAL_ADDRESS , max_temp );
                EEPROM_24C02C_Write_Byte(EEPROM2_ADDRESS , MIN_TEMP_VAL_ADDRESS , min_temp );
                EEPROM_24C02C_Write_Byte(EEPROM2_ADDRESS , LAST_TEMP_VAL_ADDRESS, last_temp );
            }
            else{ /* Nothing */ }
        }
    }
        
}

/********************** Function Declaration **********************/

static void Smart_Home_app_init(void){
    ret = EUSART_ASYNC_Init(&uart_obj);
    ret = MSSP_I2C_Init(&i2c_obj);
    ret = lcd_4bit_initialize(&Chr_Lcd_4Bit);
    ret = timer0_init(&tim_10ms);
}

static void RealTimeClock_DS1307_Date(void){
    Date[0] = '2' ;
    Date[1] = '0' ;
    
    Date[2] = ((time.Year & 0xF0) >> 4) + '0';
    Date[3] = (time.Year & 0x0F) + '0' ;
    Date[4] = '/';
    
    Date[5] = ((time.Month & 0xF0) >> 4)+ '0'  ;
    Date[6] = (time.Month & 0x0F)+ '0' ;
    Date[7] = '/';
    
    Date[8] = ((time.Day & 0xF0) >> 4)+ '0';
    Date[9] = (time.Day & 0x0F)+ '0' ;
    
    Date[10] = '\r';
    Date[11] = '\n';
    
    Time[0] = ((time.Hours & 0xF0) >> 4)+ '0';
    Time[1] = (time.Hours & 0x0F)+ '0' ;
    Time[2] = ':';
    
    Time[3] = ((time.Minutes & 0xF0) >> 4)+ '0' ;
    Time[4] = (time.Minutes & 0x0F)+ '0' ;
    Time[5] = ':';
    
    Time[6] = ((time.Seconds & 0xF0) >> 4) + '0' ;
    Time[7] = (time.Seconds & 0x0F)+ '0' ;
    
    Time[8] = '\r';
    Time[9] = '\n';
}
static void Chr_LCD_Hello_MSG(void){
    lcd_4bit_send_command(&Chr_Lcd_4Bit ,_LCD_CLEAR);
    lcd_4bit_send_command(&Chr_Lcd_4Bit , _LCD_CURSOR_OFF_DISPLAY_ON);
    
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW1 , 1 , Hello_msg_lcd);
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 5 , Hello_msg2_lcd);
    __delay_ms(1000);
    
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW1 , 1 , "                                ");
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW2 , 1 , "                                ");
    
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit , ROW1 , 1 , system_start);
    __delay_ms(1000);
}
static void Chr_LCD_Date_Time_Temp_MSG(void){
    /* LCD Display Time - Date - Temperature */
        
    /* time display */
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit ,ROW1 , 1 , "Time  ");
    Time[8] = '\0';
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit ,ROW1 , 7 , Time);
    
    /* Date display */
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit ,ROW2 , 1 , "Date ");
    Date[10] = '\0';
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit ,ROW2 , 6 , Date);
    
    /* Temperature display */
    lcd_4bit_send_string_pos(&Chr_Lcd_4Bit ,ROW3 , 1 , "Temperature ");
    temp_msg[3] = '\0';
    lcd_4bit_send_string(&Chr_Lcd_4Bit , temp_msg);
    lcd_4bit_send_custom_char(&Chr_Lcd_4Bit ,ROW3 , 16 , celsius , 1 );
    
}
static void TemperatureSensor_TC74(void){
    sint8 temp_l = temp;
    if(temp > 0){
            temp_msg[0] = '+';
        }
        else{
            temp_msg[0] = '-';
            temp_l = -temp_l;
        }
        temp_msg[1] = (temp_l/10)+'0';
        temp_msg[2] = (temp_l%10)+'0';
        temp_msg[3] = '\r';
        temp_msg[4] = '\n';
}
static void Slave_Communication(void){
    /* Send Temperature Value For Slave */
    ret = MSSP_I2C_Master_Send_Start();
    ret = MSSP_I2C_Master_Write_Blocking( (SLAVE_ADDRESS << 1) , &ack);
    ret = MSSP_I2C_Master_Send_Repeated_Start();
    ret = MSSP_I2C_Master_Write_Blocking(temp , &ack);
    ret = MSSP_I2C_Master_Send_Stop();    
}

static void TMR0_Handler(void){
    tmr0_1sec_counter++;
    tmr0_5sec_counter++;
    tmr0_10sec_counter++;
    tmr0_10ms_flag = 1;
    
    if(100 == tmr0_1sec_counter){
        tmr0_1sec_counter = 0;
        app_1sec_flag = 1 ;
    }
    else{ /* Nothing */ }
    
    if(500 == tmr0_5sec_counter){
        tmr0_5sec_counter = 0;
        app_5sec_flag = 1 ;
    }
    else{ /* Nothing */ }
    
    if(1000 == tmr0_10sec_counter){
        tmr0_10sec_counter = 0;
        app_10sec_flag = 1 ;
        app_locked_30sec++;
    }
    else{ /* Nothing */ }   
}

