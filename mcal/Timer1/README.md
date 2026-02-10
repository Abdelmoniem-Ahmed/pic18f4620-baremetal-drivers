# 🕒 Timer1 Driver – PIC18F4620

## 📌 Overview

This driver provides a clean and configurable **MCAL interface** for the **Timer1 peripheral** of the **PIC18F4620** microcontroller.

It supports **Timer and Counter modes**, **16-bit operation**, **prescaler configuration**, **oscillator control**, and **interrupt-driven execution** using a **callback mechanism**.

The driver is designed following:

- Bare-metal embedded systems best practices  
- MCAL layered architecture    
- Clear separation between configuration, control, and runtime services  

---

## 🎯 Features

- ✅ Timer mode (internal clock)
- ✅ Counter mode (external clock on **T1CKI**)
- ✅ 16-bit resolution
- ✅ Configurable prescaler (÷1 → ÷8)
- ✅ Optional interrupt support
- ✅ Callback-based ISR handling
- ✅ Interrupt priority support (if enabled)
- ✅ Optional Timer1 oscillator control
- ✅ Datasheet-compliant register access

---

## 🧱 Driver Layer

| Item        | Description                               |
|-------------|-------------------------------------------|
| Layer       | MCAL (Microcontroller Abstraction Layer) |
| MCU         | PIC18F4620                                |
| Compiler    | XC8                                       |
| Peripheral  | Timer1                                    |

---

## ⚙️ Configuration Structure

The driver is configured using the `timer1_t` structure:

```c
typedef struct {
    uint16 timer1_preload_value;
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TMR_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;
#endif
#endif
    timer1_prescaler_select_t prescaler_division;
    uint8 timer1_mode          :1;  // 0 = Timer mode, 1 = Counter mode
    uint8 timer1_counter_mode  :1;  // 0 = Synchronous, 1 = Asynchronous
    uint8 timer1_osc_cfg       :1;  // 0 = Oscillator disabled, 1 = Oscillator enabled
    uint8 timer1_reg_rw_mode   :1;  // 0 = 8-bit read/write, 1 = 16-bit read/write
} timer1_t;
```

## 🚀 Initialization Example

```c
void app_timer1_callback(void){
    /* User application code */
}

timer1_t timer1_cfg = {
    .timer1_preload_value  = 3036,
    .prescaler_division    = timer1_prescaler_div_4,
    .timer1_mode           = TIMER1_TIMER_MODE_CFG,
    .timer1_counter_mode   = TIMER1_SYNC_COUNTER_MODE_CFG,
    .timer1_osc_cfg        = TIMER1_OSC_DISABLE,
    .timer1_reg_rw_mode    = TIMER1_RD_16BIT_MODE_CFG,
    .TMR_InterruptHandler  = app_timer1_callback,
    .priority              = Interrupt_High_Priority
};

timer1_init(&timer1_cfg);

```
## 🔁 Runtime APIs

| Function              | Description                                    |
|-----------------------|------------------------------------------------|
| `timer1_init()`       | Initialize Timer1 using user configuration     |
| `timer1_Deinit()`     | Disable Timer1 and its interrupt               |
| `timer1_Read_Value()` | Read current Timer1 counter value              |
| `timer1_Write_Value()`| Write value to Timer1 register                 |

## ⏱️ Preload & Reload Mechanism

- The **preload value** is loaded during initialization.
- On every **Timer1 overflow interrupt**:
  - The preload value is **automatically reloaded**
  - The user **callback function** is executed

This mechanism enables **precise periodic timing** without relying on software counters.

## ⚠️ Important Technical Notes

### ✔ 16-bit Register Access (Datasheet-Compliant)

- Reading Or Writing to `TMR1L` automatically latches `TMR1H`
- Writing is performed as:
  1. Write `TMR1H` first
  2. Write `TMR1L` last

This behavior fully complies with the **PIC18F4620** datasheet.

### ✔ Prescaler Calculation

Prescaler values are **not calculated** inside the driver.  
They are intended to be calculated externally using a Timer Calculator App and passed as configuration.

This design keeps the driver:

- Lightweight
- Deterministic
- Hardware-focused (**MCAL compliant**)

## 🔌 Interrupt Handling

- **ISR function**: `TMR1_ISR()`
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

