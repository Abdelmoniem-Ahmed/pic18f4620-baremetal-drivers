#include "Slave_MCU_main_app.h"

/************************** Static Function Declaration **************************/
/**
 * @brief Initialize the application layer.
 *
 * This function is responsible for initializing
 * all application-level modules and ECU layers
 * before entering the main execution loop.
 */
static void slave_application_intialize(void);

static void MSSP_I2C_INTERRUPT_HANDLER(void);


static mssp_i2c_t i2c_obj = {
    .i2c_clock  = 100000,
    .i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE,
    .i2c_cfg.i2c_mode_cfg = MSSP_I2C_SLAVE_7BIT_ADDR,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE_100kHZ,
    .i2c_cfg.i2c_SMBus_Control = I2C_SMBUS_DISABLE,
    .i2c_cfg.i2c_slave_address = 0x70,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE,
#if     SMART_HOME_SLAVE_BUILD == SMART_HOME_NODE      
    .MSSP_I2C_DEFAULT_INTERRUPT_HANDLER = MSSP_I2C_INTERRUPT_HANDLER,
#endif    
};
static led_t yellow_led = {
    .port_name = PORTD_INDEX,
    .pin = PIN0,
    .led_status = GPIO_PIN_LOW
};
static ccp_t pwm = {
    .ccp_inst = CCP1_INST,
    .ccp_mode = CCP_PWM_MODE_SELECTED,
    .ccp_mode_variant = CCP_PWM_MODE,
    .PWM_Frequency = 5000,
    .timer2_prescaler_division = 4,
    
    .pin.port = PORTC_INDEX,
    .pin.pin = PIN2,
    .pin.direction = GPIO_DIRECTION_OUTPUT,
};

static dc_motor_t motor = {
    .dc_motor[0].port = PORTC_INDEX,
    .dc_motor[0].pin = PIN0,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTC_INDEX,
    .dc_motor[1].pin = PIN1,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
};

static timer2_t tim2 = {
    .prescaler_division = timer2_prescaler_div_4,
    .postscaler_division = timer2_postscaler_div_1,
    .preloaded_value = 99
};

static volatile uint8 temperature = ZERO_INIT;
static volatile uint8 mssp_i2c_transimit_data = 'y';
static volatile uint8 dummy_buffer;

static volatile uint8 system_init = 0;

static Std_ReturnType ret = E_NOT_OK; 

/************************** Function Definition **************************/
void slave_mcu_main_app(void){
    slave_application_intialize();

    while(1){
        
        if(1 == system_init){
            ret = CCP_Init(&pwm);
            ret = dc_motor_initialize(&motor);
            ret = timer2_init(&tim2);
            ret = CCP_PWM_Start(&pwm);
        }
        
        if((20 > temperature) && (temperature > 5)){
            ret = dc_motor_move_backward(&motor);
            ret = CCP_PWM_Set_Duty(&pwm ,40 );            
        }
        else if((20 <= temperature) && (35 > temperature) ){
            ret = dc_motor_move_forward(&motor);
            ret = CCP_PWM_Set_Duty(&pwm ,40 );
        }
        else if((35 <= temperature) && (45 > temperature)){
            ret = dc_motor_move_forward(&motor);
            ret = CCP_PWM_Set_Duty(&pwm ,50 );
        }
        else if((45 <= temperature) && (50 > temperature)){
            ret = dc_motor_move_forward(&motor);
            ret = CCP_PWM_Set_Duty(&pwm ,80 );
        }
        else if(50 <= temperature){
            ret = dc_motor_move_forward(&motor);
            ret = CCP_PWM_Set_Duty(&pwm ,100 );
            ret = led_turn_on(&yellow_led);
            continue;
        }
        ret = led_turn_off(&yellow_led);
    }
    
}

/************************** Helper Function **************************/
static void slave_application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = MSSP_I2C_Init(&i2c_obj);
    ret = led_initialize(&yellow_led);
}

static void MSSP_I2C_INTERRUPT_HANDLER(void){
    /* Holds Clock low (Clock Stretch) */
    I2C_CLOCK_STRETCH_ENABLE();
    
    if((SSPSTATbits.R_nW == 0) && (SSPSTATbits.D_nA == 0) ){
        /* Read Address Data From Master */
        dummy_buffer = SSPBUF;
        while(!SSPSTATbits.BF);
        temperature = SSPBUF;
    }
    else if((SSPSTATbits.R_nW == 1) && (SSPSTATbits.D_nA == 0)){
        /* Write Data To Master */
        dummy_buffer = SSPBUF; //clear address
        SSPBUF = mssp_i2c_transimit_data;
    }
    
    /* Releases Clock */
    I2C_CLOCK_STRETCH_DISABLE();
    
    if(0 == system_init){
        system_init = 1;
    }
    else{
        system_init = 2;
    }
}

