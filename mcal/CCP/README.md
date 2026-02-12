# 🎛️ CCP Driver – PIC18F4620

## 📌 Overview

This driver provides a clean and configurable **MCAL interface** for the **CCP (Capture / Compare / PWM)** of the **PIC18F4620** microcontroller.

It supports: 
- **Capture mode**
- **Compare mode**
- **PWM mode**

The driver is implemented following:

- Bare-metal embedded systems best practices  
- MCAL layered architecture    
- Clear separation between configuration, control, and runtime services  
- Callback-based interrupt handling mechanism

---

## 🎯 Features

- ✅ Capture mode (rising / falling / every 4th / every 16th edge)
- ✅ Compare mode (toggle / set / clear / special event trigger)
- ✅ PWM mode with configurable duty cycle
- ✅ Timer1 dependency handling (Capture / Compare)
- ✅ Timer2 dependency handling (PWM)
- ✅ Interrupt support (optional)
- ✅ Interrupt priority support (if enabled)
- ✅ Callback-based ISR handling
- ✅ Datasheet-compliant register access
- ✅ Clean and modular API design

---

## 🧱 Driver Layer

| Item        | Description                               |
|-------------|-------------------------------------------|
| Layer       | MCAL (Microcontroller Abstraction Layer)  |
| MCU         | PIC18F4620                                |
| Compiler    | XC8                                       |
| Peripheral  | CCP1 / CCP2                               |

---

## ⚙️ Configuration Structure

The driver is configured using the `ccp_t` structure:

```c
typedef struct{
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;
    pin_config_t pin;
#if (INTERRUPT_FEATURE_ENABLE == CCP1_INTERRUPT_FEATURE_ENABLE)
    void (* CCP_InterruptHandler)(void);
#if ( INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE)
    INTERRUPT_Priority_cfg priority;
#endif    
#endif
    
#if (CCP_CFG_PWM_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_PWM_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
    uint32 PWM_Frequency;
    uint8 timer2_prescaler_division : 2 ;
#endif    

#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_SELECTED_MODE) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_SELECTED_MODE)
    ccp_timers_cfg_t tmr13_cfg;
#endif
    
}ccp_t;
```

## 🚀 Initialization Example

### Capture Mode Example
```c
void app_ccp_callback(void){
    /* User application code */
}

ccp_t ccp1_capture_cfg = {
    .ccp_inst            = CCP1_INSTANCE,
    .ccp_mode            = CCP_CAPTURE_MODE_SELECT,
    .ccp_mode_variant    = CCP_CAPTURE_MODE_1_RISING_EDGE,
    .CCP_InterruptHandler = app_ccp_callback,
    .priority            = Interrupt_High_Priority
};

ccp_init(&ccp1_capture_cfg);
```

### Compare Mode Example
```c
ccp_t ccp1_compare_cfg = {
    .ccp_inst         = CCP1_INSTANCE,
    .ccp_mode         = CCP_COMPARE_MODE_SELECT,
    .ccp_mode_variant = CCP_COMPARE_MODE_TOGGLE_ON_MATCH
};

ccp_init(&ccp1_compare_cfg);
```

### PWM Mode Example
```c
ccp_t ccp1_pwm_cfg = {
    .ccp_inst         = CCP1_INSTANCE,
    .ccp_mode         = CCP_PWM_MODE_SELECT
};

ccp_init(&ccp1_pwm_cfg);
ccp_pwm_set_duty(&ccp1_pwm_cfg, 50);
```


## 🔁 Runtime APIs

| Function              		   | Description                                    |
|----------------------------------|------------------------------------------------|
| `CCP_Init()`          		   | Initialize CCP using user configuration        |
| `CCP_DeInit()`        		   | Disable CCP and its interrupt                  |
| `CCP_Capture_Mode_Read_Value()`  | Read captured 16-bit value       		        |
| `CCP_Compare_Mode_Set_Value()`   | Write 16-bit compare match value               |
| `CCP_PWM_Set_Duty()`  		   | Update PWM duty cycle       			        |
| `CCP1_ISR()`					   | CCP1 interrupt service routine		            |
| `CCP2_ISR()`					   | CCP2 interrupt service routine		            |

## 🎚️ Capture Mode

- Captures the value of **Timer1** on selected edge event
- Supported events:
  - Every falling edge
  - Every rising edge
  - Every 4th rising edge
  - Every 16th rising edge
- Captured value stored in `CCPRxH:CCPRxL`
- Optional interrupt on capture event  

## 🔄 Compare Mode

- Compares Timer1 value with `CCPRx` register
- Supported actions:
  - Toggle CCP pin on match
  - Set CCP pin on match
  - Clear CCP pin on match
  - Generate special event trigger (resets Timer1)
- Optional interrupt on compare match

## 🌊 PWM Mode

- Uses **Timer2** as time base
- PWM frequency determined by:
  - Timer2 prescaler
  - PR2 register value
- Duty cycle resolution: **10-bit**
- Duty cycle written using:
  - `CCPRxL`
  - `CCPxCON<5:4>`
  
### PWM Duty Cycle Formula  

```c
Duty_Cycle = (uint16)(4 * (_duty/100.0)*(PR2+1));
```

The driver handles correct bit placement internally.

## 🔌 Interrupt Handling

- **ISR function**: `CCP1_ISR()` / `CCP2_ISR()`
- Clears interrupt flag inside driver
- Callback mechanism prevents application code from being placed inside MCAL
- Supports:
  - High-priority interrupts
  - Low-priority interrupts
  - Optional interrupt priority feature

- The callback mechanism ensures:
  - Application logic is separated from MCAL
  - Clean and reusable driver architecture

## ⚠️ Important Technical Notes

### ✔ Timer Dependency

- Capture and Compare modes require Timer1
- PWM mode requires Timer2

Timers must be initialized separately before enabling CCP.

### ✔ 16-bit Register Access

- Reading `CCPRxL` latches `CCPRxH`
- Writing must follow datasheet sequence
- Fully compliant with **PIC18F4620** datasheet requirements

### ✔ Frequency Calculation Responsibility

PWM frequency calculation is not performed inside the driver.
It must be calculated externally and configured via Timer2.

This keeps the driver:

- Lightweight
- Deterministic
- Hardware-focused (MCAL compliant)

## 🧪 Error Handling

- All APIs validate input pointers
- Return values:
  - `E_OK` on success
  - `E_NOT_OK` on invalid parameters

## 👨‍💻 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer

🔗 **LinkedIn**  
https://www.linkedin.com/in/abdelmoniem-ahmed/

