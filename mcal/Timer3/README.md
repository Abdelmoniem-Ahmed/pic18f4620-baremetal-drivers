# 🕒 Timer3 Driver – PIC18F4620

## 📌 Overview

This driver provides a clean and configurable **MCAL interface** for the **Timer3 peripheral** of the **PIC18F4620** microcontroller.

It supports **Timer and Counter modes**, **16-bit operation**, **prescaler configuration**, and **interrupt-driven execution** using a **callback mechanism**.

The driver is designed following:

- Bare-metal embedded systems best practices  
- MCAL layered architecture    
- Clear separation between configuration, control, and runtime services  

---

## 🎯 Features

- ✅ Timer mode (internal clock)
- ✅ Counter mode (external clock on **T3CKI**)
- ✅ 16-bit resolution
- ✅ Configurable prescaler (÷1 → ÷8)
- ✅ Optional interrupt support
- ✅ Callback-based ISR handling
- ✅ Interrupt priority support (if enabled)
- ✅ Datasheet-compliant register access

---

## 🧱 Driver Layer

| Item        | Description                               |
|-------------|-------------------------------------------|
| Layer       | MCAL (Microcontroller Abstraction Layer) |
| MCU         | PIC18F4620                                |
| Compiler    | XC8                                       |
| Peripheral  | Timer3                                    |

---

## ⚙️ Configuration Structure

The driver is configured using the `timer3_t` structure:

```c
typedef struct {
    uint16 timer3_preloaded_value;            // Preload value for periodic timing
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TMR_InterruptHandler)(void);       // Callback for overflow interrupt
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;          // Interrupt priority
#endif
#endif
    timer3_prescaler_select_t prescaler_division; // Prescaler selection
    uint8 timer3_mode        :1;              // 0 = Timer mode, 1 = Counter mode
    uint8 timer3_reg_rw_mode :1;              // 0 = 8-bit, 1 = 16-bit read/write
    uint8 timer3_counter_mode:1;              // 0 = Sync, 1 = Async counter
    uint8 timer3_reserved    :5;              // Reserved bits
} timer3_t;
```

## 🚀 Initialization Example

```c
void app_timer3_callback(void){
    /* User application code */
}

timer3_t timer3_cfg = {
    .timer3_preloaded_value = 3036,
    .prescaler_division     = timer3_prescaler_dive_4,
    .timer3_mode            = TIMER3_TIMER_MODE_CFG,
    .timer3_reg_rw_mode     = TIMER3_RD_16BIT_MODE_CFG,
    .timer3_counter_mode    = TIMER3_SYNC_COUNTER_MODE_CFG,
    .TMR_InterruptHandler   = app_timer3_callback,
    .priority               = Interrupt_High_Priority
};

timer3_init(&timer3_cfg);
```
## 🔁 Runtime APIs

| Function              | Description                                    |
|-----------------------|------------------------------------------------|
| `timer3_init()`       | Initialize Timer3 using user configuration     |
| `timer3_Deinit()`     | Disable Timer3 and its interrupt               |
| `timer3_Read_Value()` | Read current Timer3 counter value              |
| `timer3_Write_Value()`| Write value to Timer3 register                 |

## ⏱️ Preload & Reload Mechanism

- The **preload value** is loaded during initialization.
- On every **Timer3 overflow interrupt**:
  - The preload value is **automatically reloaded**
  - The user **callback function** is executed

This mechanism enables **precise periodic timing** without relying on software counters.

## ⚠️ Important Technical Notes

### ✔ 16-bit Register Access (Datasheet-Compliant)

- Reading Or Writing to `TMR3L` automatically latches `TMR3H`
- Writing is performed as:
  1. Write `TMR3H` first
  2. Write `TMR3L` last

This behavior fully complies with the **PIC18F4620** datasheet.

### ✔ Prescaler Calculation

Prescaler values are **not calculated** inside the driver.  
They are intended to be calculated externally using a Timer Calculator App and passed as configuration.

This design keeps the driver:

- Lightweight
- Deterministic
- Hardware-focused (**MCAL compliant**)

## 🔌 Interrupt Handling

- **ISR function**: `TMR3_ISR()`
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

