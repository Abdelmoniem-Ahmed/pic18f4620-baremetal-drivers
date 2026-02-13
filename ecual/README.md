# 🟡 ECUAL – Embedded Control Unit Abstraction Layer

![C](https://img.shields.io/badge/language-C-blue)
![PIC18F4620](https://img.shields.io/badge/mcu-PIC18F4620-orange)
![ECUAL](https://img.shields.io/badge/Layer-ECUAL-yellow)

## Overview
The **ECUAL (Embedded Control Unit Abstraction Layer)** provides **high-level drivers** for external peripherals connected to the PIC18F4620 microcontroller.  

This layer abstracts low-level GPIO and MCAL handling, exposing **simple, readable APIs** for application-level development.

> ⚠️ ECUAL drivers **do not directly access MCU registers**. All low-level hardware access is handled by MCAL.

---

## Supported Drivers

| Component        | Folder          | Description                            |
|------------------|-----------------|----------------------------------------|
| LED              | `LED`           | On/Off/Toggle control                  |
| 7_Segment 	   | `7_Segment`     | BCD and direct segment control         |
| Chr LCD          | `Chr LCD`       | HD44780-based LCD, 4-bit and 8-bit mode|
| Matrix_Keypad    | `Matrix_Keypad` | Row/Column scanning with debouncing    |
| Motor            | `Motor`         | Direction and enable control           |
| Relay            | `Relay`         | Digital switching control              |

> All drivers are built on top of MCAL and are fully documented with **Doxygen-style comments**.

---

## Layer Information

- **Layer Name:** ECUAL  
- **Target MCU:** PIC18F4620  
- **Required Layer:** MCAL (GPIO, Timers, etc.)  
- **Programming Language:** C  
- **Driver Style:** Blocking / Polling-based  
- **Author:** Abdelmoniem Ahmed  
- **LinkedIn:** https://www.linkedin.com/in/abdelmoniem-ahmed/  

---

## Directory Structure

```text
ECUAL/
│
├── ecu_led/
├── ecu_button/
├── ecu_7Seg/
├── ecu_Chr_lcd/
├── ecu_keypad/
├── ecu_DC_motor/
└── ecu_relay/
```

## Getting Started
1. Include the required ECUAL driver header file in your application source file.
   ```c
   #include "ecu_led.h"
   ```

2. Configure the driver using the provided structure:

```c
led_t red_led = {
    .port_name = PORTB_INDEX,
    .pin = PIN0,
    .led_status = GPIO_PIN_LOW
};
```
3. Initialize the peripheral once at system startup:

```c
led_initialize(&red_led);
```

4. Use the exposed API during runtime:

```c
led_turn_toggle(&red_led);
```

## Design Guidelines

- All ECUAL drivers depend on MCAL — no direct MCU register access.
- Configurations are handled through structures defined in driver headers.
- Polling-based operations for simplicity; interrupts handled at MCAL level if required.
- Provides a clean and reusable API for application layer development.
- Enables rapid and maintainable application development on the PIC18F4620.

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

