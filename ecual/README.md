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

| Component        | Folder                    | Description                               |
|------------------|---------------------------|-------------------------------------------|
| LED              | `LED`                     | On/Off/Toggle control                     |
| 7_Segment 	   | `7_Segment`               | BCD and direct segment control            |
| Chr LCD          | `Chr LCD`                 | HD44780-based LCD, 4-bit and 8-bit mode   |
| Matrix_Keypad    | `Matrix_Keypad`           | Row/Column scanning with debouncing       |
| Motor            | `Motor`                   | Direction and enable control              |
| Relay            | `Relay`                   | Digital switching control                 |
| RTC DS1307       | `RealTimeClock_DS1307`    | Real-time clock reading via I2C           |
| EEPROM 24C02C    | `EEPROM_24C02C` 		   | Single-byte EEPROM read/write             |
| Temp Sensor TC74 | `Temperature_Sensor_TC74` | Digital temperature read via I2C          |

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
├── ecu_relay/
├── RealTimeClock_DS1307/
├── EEPROM_24C02C/
└── Temperature_Sensor_TC74/
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

5. For I2C-based peripherals (RTC, EEPROM, TC74), ensure the MSSP I2C driver is initialized before use.

---

## Design Guidelines

- ECUAL depends entirely on MCAL for hardware access.
- Configuration is handled through driver-specific structures.
- Polling-based operations ensure simplicity; interrupts are managed at MCAL level if needed.
- Provides clean, reusable APIs for all peripherals.
- Enables rapid and maintainable application development on PIC18F4620.


## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

