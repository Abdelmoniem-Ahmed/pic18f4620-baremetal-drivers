# 🕒 Timer0 Driver – PIC18F4620

## 📌 Overview

This driver provides a clean and configurable **MCAL interface** for the **Timer0 peripheral** of the **PIC18F4620** microcontroller.

It supports **Timer and Counter modes**, **8-bit and 16-bit operation**, **prescaler configuration**, and **interrupt-driven execution** using a **callback mechanism**.

The driver is designed following:

- Bare-metal embedded systems best practices  
- MCAL layered architecture    
- Clear separation between configuration, control, and runtime services  

---

## 🎯 Features

- ✅ Timer mode (internal clock)
- ✅ Counter mode (external clock on **T0CKI**)
- ✅ 8-bit and 16-bit resolution
- ✅ Configurable prescaler (÷2 → ÷256)
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
| Peripheral  | Timer0                                    |

---

## ⚙️ Configuration Structure

The driver is configured using the `timer0_t` structure:

```c
typedef struct{
    timer0_prescaler_select_t prescaler_division;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TMR_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;
#endif
#endif
    uint16 timer0_preload_value;
    uint8  clock_source        :1;
    uint8  prescaler_enable    :1;
    uint8  counter_edge_select :1;
    uint8  timer_resolution    :1;
} timer0_t;
```

## 🚀 Initialization Example

```c
void app_timer0_callback(void){
    /* User application code */
}

timer0_t timer0_cfg = {
    .prescaler_division   = timer0_prescaler_div_16,
    .timer0_preload_value = 3036,
    .clock_source         = TIMER0_INTERNAL_CLK_SRC_CFG,
    .prescaler_enable     = PRESCALER_ASSIGNED_CFG,
    .timer_resolution     = TIMER0_16BIT_MODE_CFG,
    .TMR_InterruptHandler = app_timer0_callback,
    .priority             = Interrupt_High_Priority
};

timer0_init(&timer0_cfg);
```
## 🔁 Runtime APIs

| Function              | Description                                    |
|-----------------------|------------------------------------------------|
| `timer0_init()`       | Initialize Timer0 using user configuration     |
| `timer0_Deinit()`     | Disable Timer0 and its interrupt               |
| `timer0_Read_Value()` | Read current Timer0 counter value              |
| `timer0_Write_Value()`| Write value to Timer0 register                 |

## ⏱️ Preload & Reload Mechanism

- The **preload value** is loaded during initialization.
- On every **Timer0 overflow interrupt**:
  - The preload value is **automatically reloaded**
  - The user **callback function** is executed

This mechanism enables **precise periodic timing** without relying on software counters.

## ⚠️ Important Technical Notes

### ✔ 16-bit Register Access (Datasheet-Compliant)

- Reading `TMR0L` automatically latches `TMR0H`
- Writing is performed as:
  1. Write `TMR0H` first
  2. Write `TMR0L` last

This behavior fully complies with the **PIC18F4620** datasheet.

### ✔ Prescaler Calculation

Prescaler values are **not calculated** inside the driver.  
They are intended to be calculated externally using a Timer Calculator App and passed as configuration.

This design keeps the driver:

- Lightweight
- Deterministic
- Hardware-focused (**MCAL compliant**)

## 🔌 Interrupt Handling

- **ISR function**: `TMR0_ISR()`
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

