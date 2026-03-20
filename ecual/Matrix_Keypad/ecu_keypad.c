/* 
 * @file    ecu_keypad.c
 * @brief   4x4 Matrix Keypad ECUAL driver implementation
 *
 * @details
 * Provides functions to initialize and read a 4x4 keypad using GPIO HAL.
 * Rows are set as outputs and columns as inputs. Pressed keys are detected by scanning rows.
 *
 * Layer: ECUAL
 * Target MCU: PIC18F
 * 
 * Author: Abdelmoniem Ahmed
 * Linkedin: https://www.linkedin.com/in/abdelmoniem-ahmed/
 * Date: 2026
 */

#include "ecu_keypad.h"

/*---------------- Button Mapping ----------------*/

static const uint8 btn_values[KEYPAD_ROW][KEYPAD_COLUMN] = { 
                                                       { '7', '8', '9', '/'},
                                                       {'4' , '5', '6', '*'},
                                                       {'1' , '2', '3', '-'},
                                                       {'#' , '0', '=', '+'}
                                                     };

static uint8 current_key = NO_KEY;
static uint8 last_key = NO_KEY;
static uint8 stable_key = NO_KEY;
static uint8 key_counter = 0;

static Keypad_State_t state = IDLE_STATE ;

static Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value );


/**
 * @brief Initialize keypad GPIO pins
 */

Std_ReturnType keypad_initialize(const keypad_t * keypad_obj){
    Std_ReturnType ret = E_OK ;
    if(NULL == keypad_obj){
        ret = E_NOT_OK;
    }
    else{
        uint8 keypad_row = ZERO_INIT , keypad_column = ZERO_INIT ;
        for(keypad_row = ZERO_INIT ; keypad_row < KEYPAD_ROW ; keypad_row++){
            ret = gpio_pin_initialize(&(keypad_obj->keypad_row_pins[keypad_row]));
        }
        for(keypad_column = ZERO_INIT ; keypad_column < KEYPAD_COLUMN ; keypad_column++){
            ret = gpio_pin_direction_initialize(&(keypad_obj->keypad_column_pins[keypad_column]));
        }
    }
    return ret;    
}

/* MUST BE CALLED EVERY 10 ms */

Std_ReturnType Keypad_Update(const keypad_t * keypad_obj ,uint8 * value){
    Std_ReturnType ret = E_NOT_OK;
 
    if((NULL == keypad_obj) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        ret = keypad_get_value(keypad_obj , &current_key);
        
        switch(state){
            case IDLE_STATE:
                if(current_key != NO_KEY){
                    key_counter = 1;
                    state = DEBOUNCE_STATE;
                }
                break;
            case DEBOUNCE_STATE :
                if(current_key == last_key){
                    key_counter++;
                    if(THRESHOLD_VAL <= key_counter){
                        stable_key = current_key;
                        state = PRESSED_STATE;
                    }
                }
                else{
                    state = IDLE_STATE;
                    key_counter = 0;
                }
                break;
            case PRESSED_STATE : 
                if(current_key == NO_KEY){
                    stable_key = NO_KEY;
                    state = IDLE_STATE;
                    key_counter = 0;
                }
                break;
            default :
                break;
            }
            last_key = current_key;
        }
    *value = stable_key;
    
    return ret;
}


/**
 * @brief Scan keypad and return pressed key
 * 
 * @param keypad_obj Pointer to keypad configuration
 * @param value Pointer to store the detected key
 * 
 * @return Std_ReturnType
 *         - E_OK     : Key read successfully
 *         - E_NOT_OK : Null pointer provided
 *
 * @note If multiple keys are pressed simultaneously, the last detected key in scan order is returned.
 */
static Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value ){
    Std_ReturnType ret = E_OK ;
    uint8 row_counter = ZERO_INIT , column_counter = ZERO_INIT , counter = ZERO_INIT ;
    uint8 return_logic = ZERO_INIT;
    if((NULL == keypad_obj) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        *value = NO_KEY;
        
        for(row_counter = ZERO_INIT ; row_counter < KEYPAD_ROW ; row_counter++){
            for(counter = ZERO_INIT ; counter < KEYPAD_ROW ; counter++){
                ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[counter]) , GPIO_PIN_LOW);
            }
            ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[row_counter]) , GPIO_PIN_HIGH );
            for(column_counter  =ZERO_INIT ; column_counter < KEYPAD_COLUMN ; column_counter++){
                ret = gpio_pin_read_logic( &(keypad_obj->keypad_column_pins[column_counter]), &return_logic );
                if(GPIO_PIN_HIGH == return_logic){
                    *value = btn_values[row_counter][column_counter];
                    return E_OK;
                }   
                
            }
        }
    }
    return ret;
}

