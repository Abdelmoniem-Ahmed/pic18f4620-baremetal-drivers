# 🕒 Timer2 Driver – PIC18F4620

## 📌 Overview

This driver provides a clean and configurable **MCAL interface** for the **Timer2 peripheral** of the **PIC18F4620** microcontroller.

It supports **8-bit Timer operation**, **prescaler and postscaler configuration**, **preload and reload mechanism** , and **interrupt-driven execution** using a **callback mechanism**.

The driver is designed following:

- Bare-metal embedded systems best practices  
- MCAL layered architecture    
- Clear separation between configuration, control, and runtime services  

---

## 🎯 Features

- ✅ 8-bit Timer mode
- ✅ Configurable prescaler (÷1 → ÷16)
- ✅ Configurable postscaler (÷1 → ÷16)
- ✅ Preload value for precise timing
- ✅ Optional interrupt support
- ✅ Callback-based ISR handling
- ✅ Interrupt priority support (if enabled)
- ✅ Datasheet-compliant register access

---

## 🧱 Driver Layer

| Item        | Description                               |
|-------------|-------------------------------------------|
| Layer       | MCAL (Microcontroller Abstraction Layer)  |
| MCU         | PIC18F4620                                |
| Compiler    | XC8                                       |
| Peripheral  | Timer2                                    |

---

## ⚙️ Configuration Structure

The driver is configured using the `timer2_t` structure:

```c
typedef struct {
    timer2_prescaler_select_t prescaler_division;   // Prescaler configuration
    timer2_postscaler_select_t postscaler_division; // Postscaler configuration
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TMR_InterruptHandler)(void);            // Callback on overflow
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;               // Interrupt priority
#endif
#endif
    uint8 preloaded_value;                          // Preload value for periodic timing
} timer2_t;

```

## 🚀 Initialization Example

```c
void app_timer2_callback(void){
    /* User application code */
}

timer2_t timer2_cfg = {
    .prescaler_division   = timer2_prescaler_div_4,
    .postscaler_division  = timer2_postscaler_div_8,
    .preloaded_value      = 100,
    .TMR_InterruptHandler = app_timer2_callback,
    .priority             = Interrupt_High_Priority
};

timer2_init(&timer2_cfg);

```
## 🔁 Runtime APIs

| Function              | Description                                    |
|-----------------------|------------------------------------------------|
| `timer2_init()`       | Initialize Timer2 using user configuration     |
| `timer2_Deinit()`     | Disable Timer2 and its interrupt               |
| `timer2_Read_Value()` | Read current Timer2 counter value              |
| `timer2_Write_Value()`| Write value to Timer2 register                 |

## ⏱️ Preload & Reload Mechanism

- The **preload value** is loaded during initialization.
- On every **Timer1 overflow interrupt**:
  - The preload value is **automatically reloaded**
  - The user **callback function** is executed

This mechanism enables **precise periodic timing** without relying on software counters.

## ⚠️ Important Technical Notes

### ✔ 8-bit Register Access (Datasheet-Compliant)

- Timer2 is 8-bit, so reads/writes are atomic.
- Preload value is used to adjust the starting point of the timer for precise intervals.


### ✔ Prescaler & Postscaler Calculation

Prescaler and postscaler values are **not calculated** inside the driver.  
Use a Timer Calculator or manual calculation to determine suitable values.

This design keeps the driver:

- Lightweight
- Deterministic
- Hardware-focused (**MCAL compliant**)

## 🔌 Interrupt Handling

- **ISR function**: `TMR2_ISR()`
- Callback mechanism prevents application code from being placed inside MCAL
- Supports:
  - High-priority interrupts
  - Low-priority interrupts
  - Optional interrupt priority feature

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

