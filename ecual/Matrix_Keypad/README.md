# Matrix Keypad Driver – ECUAL

## Overview
The Matrix Keypad driver provides a robust interface for a **4x4 matrix keypad** using GPIO pins.  

This driver is designed with **real-time constraints in mind**, making it suitable for production-level embedded systems.

Unlike basic implementations, this driver includes:
- ✅ **Non-blocking scanning**
- ✅ **Built-in software debouncing (state machine)**
- ✅ **Stable key detection**
- ✅ Designed for **real-time embedded systems**

---

## Driver Features
- Supports **4x4 matrix keypad**
- GPIO-based (no external hardware required)
- **Debounced key detection**
- **State machine implementation**
- Non-blocking (time-driven)
- Configurable row/column pins

---

## 🧠 How It Works

The driver uses:
- **Row scanning technique**
- **State machine for debouncing**

### States:
- `IDLE_STATE` → Waiting for key press
- `DEBOUNCE_STATE` → Verifying stable press
- `PRESSED_STATE` → Key confirmed

> The function `Keypad_Update()` must be called periodically every **10 ms**.

---

## Keypad Layout
The keypad mapping is fixed inside the driver:
```
7  8  9  /
4  5  6  *
1  2  3  -
#  0  =  +
```

---

## Configuration
Define keypad pins using:

```c
keypad_t keypad = {
    .keypad_row_pins = { ... },
    .keypad_column_pins = { ... }
};
```

- Rows → Output pins
- Columns → Input pins

---

## Provided APIs

1. **Initialization**

```c
  Std_ReturnType keypad_initialize(const keypad_t *keypad_obj);
```

2. **Periodic Update (IMPORTANT)**

```c
  Std_ReturnType Keypad_Update(const keypad_t *keypad_obj, uint8 *value);
```

- **Must be called every 10 ms**
- **Returns stable debounced key** 
- Returns `NO_KEY` if no key is pressed

---

## ⏱ Example Usage

### 🔹 1. Simple (Polling-Based – For Testing)

```c
uint8 key = NO_KEY;

while(1){
    Keypad_Update(&keypad, &key);

    if(key != NO_KEY){
        // Handle key press
    }

    __delay_ms(10); // Required timing
}
```

### 🔹 2. Recommended (Timer Interrupt – Real Embedded Design)

This approach uses a hardware timer to guarantee precise 10 ms periodic execution.

```c
static volatile uint8 tmr_10ms_flag = 0;

void main(void){
    uint8 current_key = NO_KEY;
    uint8 previous_key = NO_KEY;

    keypad_initialize(&matrix_keypad);
    timer1_init(&tmr_10ms);

    while(1){
        if(tmr_10ms_flag){
            tmr_10ms_flag = 0;

            Keypad_Update(&matrix_keypad, &current_key);
        }

        /* Detect key press event (rising edge) */
        if((previous_key == NO_KEY) && (current_key != NO_KEY)){
            // Handle key press
        }

        previous_key = current_key;
    }
}

/* Timer ISR */
void TMR_Handler(void){
    tmr_10ms_flag = 1;
}
```

#### 🧠 Why Timer-Based Design?

- Ensures accurate 10 ms timing
- Keeps driver non-blocking
- Suitable for RTOS / real-time systems
- Prevents CPU waste from delays

## 📁 Full Example

A complete working example (Keypad + LCD + Timer1) is available in:

`Example_projects/Matrix_keypad/`

This example demonstrates:

- Keypad input
- LCD display output
- Timer-driven scheduling

---

## 🔗 Dependencies
- GPIO HAL Driver (`hal_gpio.h`)

---

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/
